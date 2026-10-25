#pragma once
#include <string>
#include <cstdint>

class Communicator {
private:
    int socket;
public:
    explicit Communicator(int fd);
    ~Communicator();
    
    bool connect();
    void receive(void* buffer, size_t size);
    void send(const void* buffer, size_t size);
    void close();
    
};
