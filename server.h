#pragma once
#include "user_interface.h"
#include "logger.h"
#include "user_database.h"
#include "authenticator.h"
#include "data_processor.h"
#include "communicator.h"
#include <memory>

class Server {
private:
    int port;                
    int serverSocket;     
    std::unique_ptr<Logger> log;
    std::unique_ptr<UserDatabase> db;
    std::unique_ptr<Authenticator> auth;
    std::unique_ptr<DataProcessor> processor;

    void acceptClient(int clientSocket);

public:
    explicit Server(const ServerParams& params);
    ~Server();
    void start();
};
