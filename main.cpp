#include "server.h"
#include "user_interface.h"
#include "errors.h"
#include <iostream>

int main(int argc, char* argv[]) {
    try {
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
        std::cerr << e.what() << std::endl;
        return 1;
    } catch (const IOError& e) {
        std::cerr << e.what() << std::endl;
        return 2;
    } catch (const std::exception& e) {
        std::cerr << "Критическая ошибка: " << e.what() << std::endl;
        return 3;
    }
}
