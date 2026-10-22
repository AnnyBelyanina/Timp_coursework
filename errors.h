#pragma once
#include <exception>
#include <string>

class ProgramError{
protected:
    std::string message;
public:
    ProgramError(const std::string& msg);
    std::string what() const;
};

class IOError: public ProgramError{
public:
    explicit IOError(const std::string & msg);
};

class InterfaceError: public ProgramError{
public:
    explicit InterfaceError(const std::string & msg);
};

class NetworkError: public ProgramError{
public:
    explicit NetworkError(const std::string & msg);
};

class AuthError: public ProgramError{
public:
    explicit AuthError(const std::string & msg);
};
