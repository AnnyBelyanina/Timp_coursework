#pragma once
#include <string>
#include <fstream>

class Logger{
private:
    std::string filename;
    std::ofstream logFile;
    void writeLog(const std::string level,const std::string& message);

public:
    explicit Logger(const std::string& fname);
    void logInfo(const std::string& message);
    void logError(const std::string& message);
    ~Logger();
};
