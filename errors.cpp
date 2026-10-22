#include "errors.h"

ProgramError::ProgramError(const std::string& msg) : message(msg) {}

std:: string ProgramError::what() const {
    return message;
}

IOError::IOError(const std::string& msg)
    : ProgramError("IOError: " + msg) {}
    
InterfaceError::InterfaceError(const std::string& msg)
    : ProgramError("InterfaceError: " + msg) {}
    
NetworkError::NetworkError(const std::string& msg)
    : ProgramError("NetworkError: " + msg) {}
    
AuthError::AuthError(const std::string& msg)
    : ProgramError("AuthError: " + msg) {}
