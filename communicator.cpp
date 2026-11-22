/** @file
 * @author Белянина А.А.
 * @version 1.0
 * @date 22.11.2026
 * @copyright ИБСТ ПГУ
 * @warning Это учебный пример
 * @brief Реализация модуля сетевого взаимодействия
 */

#include "communicator.h"
#include "errors.h"
#include <unistd.h>
#include <sys/socket.h>

Communicator::Communicator(int fd) : socket(fd) {
    // конструктор с инициализацией дескриптора сокета
}

Communicator::~Communicator(){
    // деструктор, гарантирующий закрытие сокета при уничтожении объекта
    close();
}

bool Communicator::connect(){
    // базовая проверка валидности дескриптора сокета
    return(socket >= 0);
}

void Communicator::send(const void* buffer, size_t size){
    const char* data = static_cast<const char*>(buffer);
    size_t totalSent = 0;
    
    // циклическая отправка данных до полного завершения передачи
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
    
    // циклический прием данных до полного заполнения буфера
    while (totalRecv < size) {
        ssize_t bytes = recv(socket, data + totalRecv, size - totalRecv, 0);
        if (bytes <= 0) {
            throw NetworkError("Ошибка приема данных (клиент отключился)");
        }
        totalRecv += bytes;
    }
}

void Communicator::close() {
    // безопасное закрытие сокета и сброс дескриптора
    if (socket >= 0) {
        ::close(socket);
        socket = -1;
    }
}



