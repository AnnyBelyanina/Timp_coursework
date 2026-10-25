#pragma once
#include <string>
#include "user_database.h"

class Authenticator{
private:
    const UserDatabase& db;
    std::string calculateHash(const std::string& salt, const std::string& password) const;
public:
    explicit Authenticator(const UserDatabase& database);
    bool authenticate(const std::string& msg);
};

