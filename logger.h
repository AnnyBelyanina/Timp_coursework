/** @file
 * @author Белянина А.А.
 * @version 1.0
 * @date 22.11.2026
 * @copyright ИБСТ ПГУ
 * @warning Это учебный пример
 * @brief Заголовочный файл модуля ведения журнала работы
 */
 
#pragma once
#include <string>
#include <fstream>

/** @brief Класс журнала работы.
 * @details Запись сообщений с датой, временем и уровнем критичности в файл.
 * @warning Файл открывается в режиме дозаписи.
 */

class Logger{
private:
    std::string filename; ///< Имя файла журнала
    std::ofstream logFile;///< Поток для записи данных в файл журнала
    
    /**
     * @brief Внутренний метод записи отформатированного сообщения в файл.
     * @param[in] level Уровень критичности сообщения (например, "INFO" или "ERROR").
     * @param[in] message Текст сообщения для записи.
     */
    void writeLog(const std::string level,const std::string& message);

public:
    /**
     * @brief Конструктор класса журнала.
     * @details Открывает указанный файл в режиме дозаписи и записывает 
     *          стартовое сообщение о запуске журнала.
     * @param[in] fname Имя файла журнала.
     * @throw std::ios_base::failure, если файл не может быть открыт для записи.
     */
    explicit Logger(const std::string& fname);
    
    /**
     * @brief Запись информационного сообщения.
     * @param[in] message Текст информационного сообщения.
     */
    void logInfo(const std::string& message);
    
    /**
     * @brief Запись сообщения об ошибке.
     * @param[in] message Текст сообщения об ошибке.
     */
    void logError(const std::string& message);
    
    /**
     * @brief Деструктор класса.
     * @details Автоматически закрывает файл журнала при уничтожении объекта.
     */
    ~Logger();
};
