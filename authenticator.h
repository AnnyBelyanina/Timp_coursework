/** @file
 * @author Белянина А.А.
 * @version 1.0
 * @date 22.11.2026
 * @copyright ИБСТ ПГУ
 * @warning Это учебный пример
 * @brief Заголовочный файл модуля аутентификации клиентов
 */
 
#pragma once
#include <string>
#include "user_database.h"

/** @brief Класс аутентификации клиентов.
 * @details Использует хеш-функцию SHA-256 и "соль" SALT16 для безопасной 
 * проверки подлинности пользователя по открытому каналу связи.
 * @warning Требует подключения сторонней криптографической библиотеки Crypto++.
 */
class Authenticator{
private:
    const UserDatabase& db; ///< Ссылка на объект базы данных пользователей
    
    /**
     * @brief Вычисление хеша SHA-256 от соли и пароля.
     * @param[in] salt Соль (строка из 16 шестнадцатеричных цифр).
     * @param[in] password Пароль пользователя.
     * @return Хеш в виде строки шестнадцатеричных цифр (64 символа).
     */
    std::string calculateHash(const std::string& salt, const std::string& password) const;
public:
    /**
     * @brief Конструктор класса.
     * @param[in] database Ссылка на объект базы данных пользователей.
     */
    explicit Authenticator(const UserDatabase& database);
    
    /**
     * @brief Аутентификация клиента.
     * @details Извлекает логин, соль и хеш из сообщения, находит пользователя в базе,
     * вычисляет эталонный хеш и сравнивает его с полученным от клиента.
     * @param[in] msg Сообщение аутентификации вида LOGIN||SALT16||HASH64.
     * @return true при успешной аутентификации.
     * @throw AuthError, если сообщение слишком короткое или пользователь не найден в базе.
     */
    bool authenticate(const std::string& msg);
};

