#include "communicator.h"
#include "errors.h"
#include <unistd.h>
#include <sys/socket.h>

Communicator::Communicator(int fd) : socket(fd) {}

Communicator::~Communicator(){
    close();
}

bool Communicator::connect(){
    return(socket >= 0);
}

void Communicator::send(const void* buffer, size_t size){
    const char* data = static_cast<const char*>(buffer);
    size_t totalSent = 0;
    
    while (totalSent < size){
        ssize_t bytes = ::send(socket, data + totalSent, size - totalSent, 0);
        if (bytes <= 0) {
            throw NetworkError("Ошибка отправки данных");
        }
        totalSent += bytes;
    }
}

void Communicator::receive(void* buffer, size_t size) {
    char* data = static_cast<char*>(buffer);
    size_t totalRecv = 0;
    
    while (totalRecv < size) {
        ssize_t bytes = recv(socket, data + totalRecv, size - totalRecv, 0);
        if (bytes <= 0) {
            throw NetworkError("Ошибка приема данных (клиент отключился)");
        }
        totalRecv += bytes;
    }
}

void Communicator::close() {
    if (socket >= 0) {
        ::close(socket);
        socket = -1;
    }
}



