/** @file
 * @author Белянина А.А.
 * @version 1.0
 * @date 22.11.2026
 * @copyright ИБСТ ПГУ
 * @warning Это учебный пример
 * @brief Реализация модуля работы с базой пользователей
 */
 
#include "user_database.h"
#include "errors.h"
#include <fstream>
#include <iostream>

UserDatabase::UserDatabase(const std::string& fname) : filename(fname){
    // конструктор с инициализацией имени файла базы данных
}

bool UserDatabase::load(){
    // открытие файла базы данных для чтения
    std::ifstream file(filename);
    
    // проверка успешности открытия и возбуждение исключения при ошибке
    if (!file.is_open()){
        throw IOError("Не удалось открыть файл базы данных: " + filename);
    }
    
    std::string line;
    // построчное чтение файла
    while (std::getline(file,line)){
        if (line.empty()) continue; // пропуск пустых строк
        
        // поиск разделителя логина и пароля
        size_t pos = line.find(":");
        if (pos != std::string::npos){
            std::string login = line.substr(0,pos);
            std::string password = line.substr(pos + 1);
            // сохранение пары логин-пароль в ассоциативный массив
            users[login] = password;
        }
    }
    return true;
}

bool UserDatabase::findUser (const std::string& login, std::string& outPassword) const{
    // поиск пользователя в map по ключу (логину)
    auto it = users.find(login);
    
    // если пользователь найден, копируем пароль и возвращаем true
    if (it != users.end()){
        outPassword = it->second;
        return true;
    }
    return false;
}
