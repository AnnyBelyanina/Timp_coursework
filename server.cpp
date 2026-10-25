#include "server.h"
#include "errors.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <vector>
#include <cmath> 

Server::Server(const ServerParams& params) 
    : port(params.port), serverSocket(-1) {
    
    // Инициализация всех модулей
    log = std::make_unique<Logger>(params.logFile);
    
    db = std::make_unique<UserDatabase>(params.databaseFile);
    log->logInfo("Загрузка базы данных из файла: " + params.databaseFile);
    db->load();
    log->logInfo("База данных успешно загружена.");
    
    auth = std::make_unique<Authenticator>(*db);
    processor = std::make_unique<DataProcessor>();
}

Server::~Server() {
    if (serverSocket >= 0) {
        close(serverSocket);
    }
}

void Server::start() {
    // 1. Создаем TCP сокет
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) throw IOError("Не удалось создать сокет");

    // Настройка: разрешаем переиспользовать порт сразу после перезапуска
    int opt = 1;
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // 2. Привязываем сокет к порту
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(serverSocket, (struct sockaddr *)&address, sizeof(address)) < 0) {
        throw IOError("Не удалось привязать сокет к порту " + std::to_string(port));
    }

    // 3. Начинаем слушать
    if (listen(serverSocket, 10) < 0) {
        throw IOError("Ошибка при прослушивании сокета");
    }

    log->logInfo("Сервер запущен на порту " + std::to_string(port));

    // 4. Главный бесконечный цикл
    while (true) {
        struct sockaddr_in clientAddr;
        socklen_t clientLen = sizeof(clientAddr);
        
        // Ждем подключения клиента
        int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientLen);
        if (clientSocket < 0) {
            log->logError("Ошибка при приеме соединения");
            continue;
        }

        log->logInfo("Клиент подключился: " + std::string(inet_ntoa(clientAddr.sin_addr)));

        // Обрабатываем клиента
        try {
            acceptClient(clientSocket);
        } catch (const std::exception& e) {
            log->logError(std::string("Ошибка при обработке клиента: ") + e.what());
        }
    }
}

void Server::acceptClient(int clientSocket) {
    Communicator comm(clientSocket);

    // Аутентификация
    // Читаем первые 4 байта
    uint32_t firstBytes = 0;
    comm.receive(&firstBytes, sizeof(firstBytes));
    
    std::string authMsg;
    
    // Если это разумная длина (< 1000), читаем столько байт
    if (firstBytes < 1000 && firstBytes > 0) {
        authMsg.resize(firstBytes);
        comm.receive(&authMsg[0], firstBytes);
    } else {
        // Иначе это часть данных, читаем ещё 80 байт (итого 84 байта: LOGIN + SALT16 + HASH64)
        authMsg.resize(4);
        memcpy(&authMsg[0], &firstBytes, 4);
        
        std::string remaining(80, '\0');
        comm.receive(&remaining[0], 80);
        authMsg += remaining;
    }
    
    bool isAuth = auth->authenticate(authMsg);

    if (isAuth) {
        std::string okMsg = "OK\n";
        comm.send(okMsg.data(), okMsg.length());
        log->logInfo("Клиент успешно авторизован.");
    } else {
        std::string errMsg = "ERR\n";
        comm.send(errMsg.data(), errMsg.length());
        log->logError("Ошибка аутентификации. Разрыв соединения.");
        return;
    }

    // Приём данных
    uint32_t N = 0;
    comm.receive(&N, sizeof(N));

    std::vector<double> results;
    results.reserve(N);

    for (uint32_t i = 0; i < N; ++i) {
        uint32_t S = 0;
        comm.receive(&S, sizeof(S));

        std::vector<double> vec(S);
        if (S > 0) {
            comm.receive(vec.data(), S * sizeof(double));
        }

        double mean = processor->calculateMean(vec);

        if (std::isinf(mean)) {
            if (mean > 0) {
                log->logInfo("Переполнение вверх (+inf) при вычислении среднего для вектора " + std::to_string(i + 1));
            } else {
                log->logInfo("Переполнение вниз (-inf) при вычислении среднего для вектора " + std::to_string(i + 1));
            }
        }

        results.push_back(mean);
        
        // Отправляем промежуточный результат после каждого вектора
        comm.send(&mean, sizeof(double));
    }

    // Отправка общего результата
    comm.send(&N, sizeof(N));
    if (N > 0) {
        comm.send(results.data(), N * sizeof(double));
    }

    log->logInfo("Вычисления завершены, результаты отправлены");
    log->logInfo("Соединение с клиентом закрыто");
}
