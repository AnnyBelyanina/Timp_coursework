#pragma once
#include <string>

struct ServerParams {
    std::string databaseFile;
    std::string logFile;
    int port;
};

class UserInterface{
private:
    ServerParams params;
public:
    UserInterface();
    bool parseArgs(int argc, char* argv[]);
    void showHelp();
    
    ServerParams getParams() const;
};
