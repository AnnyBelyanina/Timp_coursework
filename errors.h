/** @file
 * @author Белянина А.А.
 * @version 1.0
 * @date 22.11.2026
 * @copyright ИБСТ ПГУ
 * @warning Это учебный пример
 * @brief Заголовочный файл модуля исключений
 */
 
#pragma once

#include <exception>
#include <string>

/** @brief Базовый класс исключений программы.
 * @details Все классы исключений наследуются от std::exception.
 * Хранит текстовое сообщение об ошибке.
 */

class ProgramError : public std::exception {
protected:
    std::string message; ///< Текст сообщения об ошибке
public:
    /**
     * @brief Конструктор класса исключения.
     * @param[in] msg Текст сообщения об ошибке.
     */
    ProgramError(const std::string& msg);
    /**
     * @brief Возвращает текст сообщения об ошибке.
     * @return C-строка с описанием ошибки (переопределение метода std::exception::what).
     */
    const char* what() const noexcept override;
};
/** @brief Исключение ввода-вывода (ошибки работы с файлами). */
class IOError : public ProgramError {
public:
    /**
     * @brief Конструктор исключения ввода-вывода.
     * @param[in] msg Описание ошибки.
     */
    IOError(const std::string& msg);
};

/** @brief Исключение пользовательского интерфейса (ошибки параметров командной строки). */
class InterfaceError : public ProgramError {
public:
    /**
     * @brief Конструктор исключения интерфейса.
     * @param[in] msg Описание ошибки.
     */
    InterfaceError(const std::string& msg);
};

/** @brief Сетевое исключение (ошибки сокетов и соединения). */
class NetworkError : public ProgramError {
public:
    /**
     * @brief Конструктор сетевого исключения.
     * @param[in] msg Описание ошибки.
     */
    NetworkError(const std::string& msg);
};

/** @brief Исключение аутентификации (ошибки проверки логина/пароля). */
class AuthError : public ProgramError {
public:
    /**
     * @brief Конструктор исключения аутентификации.
     * @param[in] msg Описание ошибки.
     */
    AuthError(const std::string& msg);
};

