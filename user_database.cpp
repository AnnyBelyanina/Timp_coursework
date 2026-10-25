#include "user_database.h"
#include "errors.h"
#include <fstream>
#include <iostream>

UserDatabase::UserDatabase(const std::string& fname) : filename(fname){
    
}

bool UserDatabase::load(){
    std::ifstream file(filename);
    
    if (!file.is_open()){
        throw IOError("Не удалось открыть файл базы данных: " + filename);
    }
    
    std::string line;
    while (std::getline(file,line)){
        if (line.empty()) continue;
        
        size_t pos = line.find(":");
        if (pos != std::string::npos){
            std::string login = line.substr(0,pos);
            std::string password = line.substr(pos + 1);
            users[login] = password;
        }
    }
    return true;
}

bool UserDatabase::findUser (const std::string& login, std::string& outPassword) const{
    auto it = users.find(login);
    
    if (it != users.end()){
        outPassword = it->second;
        return true;
    }
    return false;
}
