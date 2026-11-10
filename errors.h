#ifndef ERRORS_H
#define ERRORS_H

#include <exception>
#include <string>

class ProgramError : public std::exception {
protected:
    std::string message;
public:
    ProgramError(const std::string& msg);
    const char* what() const noexcept override;
};

class IOError : public ProgramError {
public:
    IOError(const std::string& msg);
};

class InterfaceError : public ProgramError {
public:
    InterfaceError(const std::string& msg);
};

class NetworkError : public ProgramError {
public:
    NetworkError(const std::string& msg);
};

class AuthError : public ProgramError {
public:
    AuthError(const std::string& msg);
};

#endif // ERRORS_H
