#include "authenticator.h"
#include "errors.h"

#include <cryptopp/sha.h>
#include <cryptopp/hex.h>
#include <cryptopp/filters.h>

Authenticator::Authenticator (const UserDatabase& database) : db (database){
    
}

std::string Authenticator::calculateHash(const std::string& salt, const std::string& password) const {
    std::string data = salt + password;
    std::string hash;
    
    CryptoPP::SHA256 sha;
    CryptoPP::StringSource(data, true,
        new CryptoPP::HashFilter(sha,
            new CryptoPP::HexEncoder(
                new CryptoPP::StringSink(hash))));
                
    return hash;
}

bool Authenticator::authenticate(const std::string& msg){
    const size_t FIXED_LEN = 16 + 64;
        
        if (msg.length() < FIXED_LEN){
            throw AuthError("Слишком короткое аутентификационное сообщение");
        }
        
        std::string login = msg.substr(0, msg.length() - FIXED_LEN);
        std::string salt = msg.substr(msg.length() - FIXED_LEN, 16);
        std::string recvHash = msg.substr(msg.length() - 64);
        
        std::string password;
        if (!db.findUser(login,password)){
            throw AuthError("Пользователь не найден: " + login);
        }
        
        std::string calcHash = calculateHash(salt, password);
        
        return calcHash == recvHash;
    
}
