/** @file
 * @author Белянина А.А.
 * @version 1.0
 * @date 22.11.2026
 * @copyright ИБСТ ПГУ
 * @warning Это учебный пример
 * @brief Точка входа в программу vcalc_server
 */
 
#include "server.h"
#include "user_interface.h"
#include "errors.h"
#include <iostream>

int main(int argc, char* argv[]) {
    try {
        // создание объекта интерфейса и разбор параметров командной строки
        UserInterface ui;
        
        // Разбор параметров (если передан -h, программа покажет справку и выйдет)
        if (!ui.parseArgs(argc, argv)) {
            return 0;
        }

        // Создаем и запускаем сервер с полученными параметрами
        Server server(ui.getParams());
        server.start();
        
        return 0;

    } catch (const InterfaceError& e) {
        // обработка ошибок пользовательского интерфейса
        std::cerr << e.what() << std::endl;
        return 1;
    } catch (const IOError& e) {
        // обработка ошибок ввода-вывода
        std::cerr << e.what() << std::endl;
        return 2;
    } catch (const std::exception& e) {
        // перехват любых других критических исключений
        std::cerr << "Критическая ошибка: " << e.what() << std::endl;
        return 3;
    }
}
