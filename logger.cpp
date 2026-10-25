#include "logger.h"
#include "errors.h"
#include <chrono>
#include <iomanip>
#include <sstream>
#include <iostream>

Logger::Logger(const std::string& fname) : filename(fname) {
    logFile.open(filename, std::ios::app);
    
    if (!logFile.is_open()){
        throw IOError("Не удалось открыть файл журнала");
    }
    
    logInfo("Журнал работы программы инициализирован");
}

Logger::~Logger(){
    if (logFile.is_open()){
        logFile.close();
    }
}

void Logger::writeLog(const std::string level, const std::string& message) {
    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);
    
    std::stringstream ss;
    ss << "[" << std::put_time(std::localtime(&time_t_now), "%H:%M:%S %d-%m-%Y")
        << "] [" << level << "] " << message << std::endl;
        
    std::string logEntry = ss.str();
    
    if (logFile.is_open()){
        logFile << logEntry;
        logFile.flush(); 
    }
    
    if (level == "ERROR"){
        std::cerr << logEntry;
    }
}

void Logger::logInfo(const std::string& message){
    writeLog("INFO", message);
}

void Logger::logError(const std::string& message) {
    writeLog("ERROR", message);
}
