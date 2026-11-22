/** @file
 * @author Белянина А.А.
 * @version 1.0
 * @date 22.11.2026
 * @copyright ИБСТ ПГУ
 * @warning Это учебный пример
 * @brief Заголовочный файл модуля пользовательского интерфейса
 */
#pragma once
#include <string>

/** @brief Структура параметров программы. */
struct ServerParams {
    std::string databaseFile; ///< Имя файла базы клиентов
    std::string logFile; ///< Имя файла журнала
    int port; ///< Номер порта сервера
};

/** @brief Класс пользовательского интерфейса.
 * @details Разбор параметров командной строки с помощью boost::program_options.
 * @warning Требует установки библиотеки boost.
 */
class UserInterface{
private:
    ServerParams params; ///< Текущие параметры программы
public:
    UserInterface();
    
    /**
     * @brief Разбор параметров командной строки.
     * @param[in] argc Количество аргументов.
     * @param[in] argv Массив аргументов.
     * @return true, если разбор успешен; false, если выведена справка.
     * @throw InterfaceError, при неизвестном параметре или отсутствии значения.
     */
    bool parseArgs(int argc, char* argv[]);
    
    /** 
     * @brief Вывод справки по использованию программы.
     * @details Отображает информацию о доступных параметрах командной строки и их значениях по умолчанию.
     */
    void showHelp();
    
    /** 
     * @brief Получение текущих параметров программы.
     * @return Структура ServerParams с текущими настройками.
     */
    ServerParams getParams() const;
};
