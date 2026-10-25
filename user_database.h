#pragma once
#include <string>
#include <map>

class UserDatabase{
private:
    std::string filename;
    std::map<std::string, std::string> users;
public:
    explicit UserDatabase(const std::string& fname);
    bool load();
    bool findUser(const std::string& login, std::string& outPassword) const;
};
