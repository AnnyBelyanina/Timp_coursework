/** @file
 * @author Белянина А.А.
 * @version 1.0
 * @date 22.11.2026
 * @copyright ИБСТ ПГУ
 * @warning Это учебный пример
 * @brief Реализация модуля ведения журнала работы
 */
 
#include "logger.h"
#include "errors.h"
#include <chrono>
#include <iomanip>
#include <sstream>
#include <iostream>

Logger::Logger(const std::string& fname) : filename(fname) {
    // открытие файла в режиме дозаписи (app) 
    logFile.open(filename, std::ios::app);
    
    // проверка успешности открытия файла и возбуждение исключения при ошибке
    if (!logFile.is_open()){
        throw IOError("Не удалось открыть файл журнала");
    }
    
    // запись стартового сообщения об инициализации
    logInfo("Журнал работы программы инициализирован");
}

Logger::~Logger(){
    // безопасное закрытие файла при уничтожении объекта
    if (logFile.is_open()){
        logFile.close();
    }
}

void Logger::writeLog(const std::string level, const std::string& message) {
    // получение текущего времени системы
    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);
    
    // форматирование строки записи журнала: [Время] [Уровень] Сообщение
    std::stringstream ss;
    ss << "[" << std::put_time(std::localtime(&time_t_now), "%H:%M:%S %d-%m-%Y")
        << "] [" << level << "] " << message << std::endl;
        
    std::string logEntry = ss.str();
    
    // запись в файл и принудительная синхронизация буфера на диск
    if (logFile.is_open()){
        logFile << logEntry;
        logFile.flush(); 
    }
    
    // дублирование критических ошибок в стандартный поток ошибок (stderr)
    if (level == "ERROR"){
        std::cerr << logEntry;
    }
}

void Logger::logInfo(const std::string& message){
    // вызов общего метода записи с уровнем INFO
    writeLog("INFO", message);
}

void Logger::logError(const std::string& message) {
    // вызов общего метода записи с уровнем ERROR
    writeLog("ERROR", message);
}
