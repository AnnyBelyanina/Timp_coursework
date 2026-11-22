/** @file
 * @author Белянина А.А.
 * @version 1.0
 * @date 22.11.2026
 * @copyright ИБСТ ПГУ
 * @warning Это учебный пример
 * @brief Реализация иерархии классов исключений программы
 */
 
#include "errors.h"

// Конструктор базового класса исключения с инициализацией сообщения
ProgramError::ProgramError(const std::string& msg) : message(msg) {}

// Переопределение виртуального метода std::exception для возврата C-строки
const char* ProgramError::what() const noexcept {
    return message.c_str();
}

// Конструктор исключения ввода-вывода с добавлением префикса к сообщению
IOError::IOError(const std::string& msg)
    : ProgramError("IOError: " + msg) {}
  
// Конструктор исключения пользовательского интерфейса с добавлением префикса
InterfaceError::InterfaceError(const std::string& msg)
    : ProgramError("InterfaceError: " + msg) {}

// Конструктор сетевого исключения с добавлением префикса
NetworkError::NetworkError(const std::string& msg)
    : ProgramError("NetworkError: " + msg) {}

// Конструктор исключения аутентификации с добавлением префикса    
AuthError::AuthError(const std::string& msg)
    : ProgramError("AuthError: " + msg) {}
