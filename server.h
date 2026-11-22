/** @file
 * @author Белянина А.А.
 * @version 1.0
 * @date 22.11.2026
 * @copyright ИБСТ ПГУ
 * @warning Это учебный пример
 * @brief Заголовочный файл модуля сетевого взаимодействия
 */
 
#pragma once
#include "user_interface.h"
#include "logger.h"
#include "user_database.h"
#include "authenticator.h"
#include "data_processor.h"
#include "communicator.h"
#include <memory>

/** @brief Класс сервера.
 * @details Координирует работу всех подсистем: аутентификации, обработки данных и сетевого взаимодействия.
 * @warning Сервер работает в однопоточном режиме и обслуживает клиентов по очереди.
 */
class Server {
private:
    int port;           ///< Номер порта для прослушивания     
    int serverSocket;   ///< Дескриптор серверного сокета
    std::unique_ptr<Logger> log; ///< Указатель на объект журнала работы
    std::unique_ptr<UserDatabase> db; ///< Указатель на объект базы пользователей
    std::unique_ptr<Authenticator> auth; ///< Указатель на объект аутентификации
    std::unique_ptr<DataProcessor> processor; ///< Указатель на объект обработки данных
    
    /**
     * @brief Обслуживание подключенного клиента.
     * @details Выполняет аутентификацию, прием данных, вычисления и отправку результата.
     * @param[in] clientSocket Дескриптор сокета подключенного клиента.
     * @throw NetworkError при ошибках сетевого обмена.
     * @throw AuthError при ошибках аутентификации.
     */
    void acceptClient(int clientSocket);

public:
    /**
     * @brief Конструктор класса сервера.
     * @details Инициализирует все подсистемы на основе переданных параметров.
     * @param[in] params Структура параметров сервера (порт, имена файлов и т.д.).
     */
    explicit Server(const ServerParams& params);
    
    /**
     * @brief Деструктор класса сервера.
     * @details Автоматически освобождает ресурсы всех подсистем и закрывает серверный сокет.
     */
    ~Server();
    
    /**
     * @brief Запуск сервера.
     * @details Инициализирует сетевой сокет, начинает прослушивание порта и входит в цикл ожидания клиентов.
     * @throw NetworkError при ошибках создания или привязки сокета.
     */
    void start();
};
