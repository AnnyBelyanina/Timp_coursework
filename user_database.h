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
#include <map>

/** @brief Класс базы данных пользователей.
 * @details Отвечает за чтение текстового файла с парами "логин:пароль" 
 * и хранение этих данных в памяти для последующего поиска.
 * @warning Некорректные строки в файле базы данных (без разделителя) игнорируются.
 */
 
class UserDatabase{
private:
    std::string filename; ///< Имя файла базы данных
    std::map<std::string, std::string> users; ///< Таблица пользователей (логин : пароль)
public:
    /**
     * @brief Конструктор класса.
     * @param[in] fname Имя файла базы данных для последующей загрузки.
     */
    explicit UserDatabase(const std::string& fname);
    
    /**
     * @brief Загрузка базы пользователей из файла.
     * @details Читает файл построчно, разделяя логин и пароль по символу ':'.
     * @return true при успешной загрузке файла.
     * @throw IOError, если файл не найден или не может быть открыт.
     */
    bool load();
    
    /**
     * @brief Поиск пользователя по логину.
     * @details Выполняет поиск записи в загруженной таблице пользователей.
     * @param[in] login Логин клиента для поиска.
     * @param[out] outPassword Пароль клиента (заполняется только при успешном поиске).
     * @return true, если пользователь найден; false в противном случае.
     */
    bool findUser(const std::string& login, std::string& outPassword) const;
};
