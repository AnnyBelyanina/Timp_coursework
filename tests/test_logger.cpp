#include <UnitTest++/UnitTest++.h>
#include <fstream>
#include <iostream>
#include <string>
#include "logger.h"

#define TEST_LOG_FILE "test_run.log"

struct LoggerFixture {
    LoggerFixture() { std::remove(TEST_LOG_FILE); }
    ~LoggerFixture() { std::remove(TEST_LOG_FILE); }
};

SUITE(LoggerTest) {
    TEST_FIXTURE(LoggerFixture, CreateLogFile) { // Тест 1.1
        Logger log(TEST_LOG_FILE);
        std::ifstream f(TEST_LOG_FILE);
        bool isOpen = f.is_open();
        std::string line;
        std::getline(f, line);
        bool hasInfo = line.find("[INFO]") != std::string::npos;
        std::cout << "Тест 1.1: файл открыт=" << (isOpen ? "true" : "false") 
                  << ", содержит [INFO]=" << (hasInfo ? "true" : "false") << std::endl;
        CHECK(isOpen);
        CHECK(hasInfo);
    }

    TEST_FIXTURE(LoggerFixture, LogInfoFormat) { // Тест 2.1
        Logger log(TEST_LOG_FILE);
        log.logInfo("Test");
        std::ifstream f(TEST_LOG_FILE);
        std::string line;
        std::getline(f, line); std::getline(f, line);
        bool hasInfo = line.find("[INFO]") != std::string::npos;
        bool hasText = line.find("Test") != std::string::npos;
        std::cout << "Тест 2.1: содержит [INFO]=" << (hasInfo ? "true" : "false") 
                  << ", содержит 'Test'=" << (hasText ? "true" : "false") << std::endl;
        CHECK(hasInfo);
        CHECK(hasText);
    }

    TEST_FIXTURE(LoggerFixture, LogErrorFormat) { // Тест 2.2
        Logger log(TEST_LOG_FILE);
        log.logError("Error test");
        std::ifstream f(TEST_LOG_FILE);
        std::string line;
        std::getline(f, line); std::getline(f, line);
        bool hasError = line.find("[ERROR]") != std::string::npos;
        bool hasText = line.find("Error test") != std::string::npos;
        std::cout << "Тест 2.2: содержит [ERROR]=" << (hasError ? "true" : "false") 
                  << ", содержит 'Error test'=" << (hasText ? "true" : "false") << std::endl;
        CHECK(hasError);
        CHECK(hasText);
    }

    TEST_FIXTURE(LoggerFixture, AppendMode) { // Тест 3.1
        { Logger log(TEST_LOG_FILE); log.logInfo("First"); }
        { Logger log(TEST_LOG_FILE); log.logInfo("Second"); }
    
        std::ifstream f(TEST_LOG_FILE);
        std::string line;
        bool hasFirst = false;
        bool hasSecond = false;
    
        while (std::getline(f, line)) {
            if (line.find("First") != std::string::npos) hasFirst = true;
            if (line.find("Second") != std::string::npos) hasSecond = true;
        }
    
        std::cout << "Тест 3.1: содержит 'First'=" << (hasFirst ? "true" : "false") 
              << ", содержит 'Second'=" << (hasSecond ? "true" : "false") << std::endl;
        CHECK(hasFirst);
        CHECK(hasSecond);
    }
}
