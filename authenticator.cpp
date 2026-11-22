/** @file
 * @author Белянина А.А.
 * @version 1.0
 * @date 22.11.2026
 * @copyright ИБСТ ПГУ
 * @warning Это учебный пример
 * @brief Реализация модуля аутентификации клиентов
 */
 
#include "authenticator.h"
#include "errors.h"

#include <cryptopp/sha.h>
#include <cryptopp/hex.h>
#include <cryptopp/filters.h>

Authenticator::Authenticator (const UserDatabase& database) : db (database){
    // конструктор с сохранением ссылки на объект базы данных
}

std::string Authenticator::calculateHash(const std::string& salt, const std::string& password) const {
    // конкатенация соли и пароля
    std::string data = salt + password;
    std::string hash;
    
    // вычисление SHA-256 и кодирование результата в HEX-строку с помощью фильтров CryptoPP
    CryptoPP::SHA256 sha;
    CryptoPP::StringSource(data, true,
        new CryptoPP::HashFilter(sha,
            new CryptoPP::HexEncoder(
                new CryptoPP::StringSink(hash))));
                
    return hash;
}

bool Authenticator::authenticate(const std::string& msg){
    const size_t FIXED_LEN = 16 + 64; // длина SALT16 + HASH64
        
        // проверка минимальной длины сообщения
        if (msg.length() < FIXED_LEN){
            throw AuthError("Слишком короткое аутентификационное сообщение");
        }
        
        // извлечение частей сообщения: логин, соль и полученный хеш
        std::string login = msg.substr(0, msg.length() - FIXED_LEN);
        std::string salt = msg.substr(msg.length() - FIXED_LEN, 16);
        std::string recvHash = msg.substr(msg.length() - 64);
        
        std::string password;
        // поиск пользователя в базе данных
        if (!db.findUser(login,password)){
            throw AuthError("Пользователь не найден: " + login);
        }
        
        // вычисление эталонного хеша и сравнение с полученным от клиента
        std::string calcHash = calculateHash(salt, password);
        
        return calcHash == recvHash;
    
}
