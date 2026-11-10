#include <UnitTest++/UnitTest++.h>
#include <iostream>
#include "user_interface.h"
#include "errors.h" 

SUITE(HelpTest) {
    TEST(NoParams) { // Тест 1.1
        UserInterface ui;
        char arg1[] = "vcalc_server";
        char* argv[] = {arg1, nullptr};  
        int argc = sizeof(argv) / sizeof(nullptr) - 1;
        bool result = ui.parseArgs(argc, argv);
        std::cout << "=== Модуль UserInterface ===" << std::endl;
        std::cout << "Тест 1.1: parseArgs вернул " << (result ? "true" : "false") << std::endl;
        REQUIRE CHECK(!result);
    }

    TEST(ShortHelp) { // Тест 1.2
        UserInterface ui;
        char arg1[] = "vcalc_server";
        char arg2[] = "-h";
        char* argv[] = {arg1, arg2, nullptr};
        int argc = sizeof(argv) / sizeof(nullptr) - 1;
        bool result = ui.parseArgs(argc, argv);
        std::cout << "Тест 1.2: parseArgs вернул " << (result ? "true" : "false") << std::endl;
        REQUIRE CHECK(!result);
    }

    TEST(LongHelp) { // Тест 1.3
        UserInterface ui;
        char arg1[] = "vcalc_server";
        char arg2[] = "--help";
        char* argv[] = {arg1, arg2, nullptr};
        int argc = sizeof(argv) / sizeof(nullptr) - 1;
        bool result = ui.parseArgs(argc, argv);
        std::cout << "Тест 1.3: parseArgs вернул " << (result ? "true" : "false") << std::endl;
        REQUIRE CHECK(!result);
    }

    TEST(HelpAndPort) { // Тест 1.4
        UserInterface ui;
        char arg1[] = "vcalc_server";
        char arg2[] = "-h";
        char arg3[] = "-p";
        char arg4[] = "44444";
        char* argv[] = {arg1, arg2, arg3, arg4, nullptr};
        int argc = sizeof(argv) / sizeof(nullptr) - 1;
        bool result = ui.parseArgs(argc, argv);
        std::cout << "Тест 1.4: parseArgs вернул " << (result ? "true" : "false") << std::endl;
        REQUIRE CHECK(!result);
    }

    TEST(PortAndHelp) { // Тест 1.5
        UserInterface ui;
        char arg1[] = "vcalc_server";
        char arg2[] = "-p";
        char arg3[] = "44444";
        char arg4[] = "-h";
        char* argv[] = {arg1, arg2, arg3, arg4, nullptr};
        int argc = sizeof(argv) / sizeof(nullptr) - 1;
        bool result = ui.parseArgs(argc, argv);
        std::cout << "Тест 1.5: parseArgs вернул " << (result ? "true" : "false") << std::endl;
        REQUIRE CHECK(!result);
    }
}

SUITE(WorkParamsTest) {
    TEST(RunOnly) { // Тест 2.1
        UserInterface ui;
        char arg1[] = "vcalc_server";
        char arg2[] = "--run";
        char* argv[] = {arg1, arg2, nullptr};
        int argc = sizeof(argv) / sizeof(nullptr) - 1;
        bool result = ui.parseArgs(argc, argv);
        int port = ui.getParams().port;
        std::cout << "Тест 2.1: parseArgs=" << (result ? "true" : "false") 
                  << ", port=" << port << std::endl;
        REQUIRE CHECK(result);
        CHECK_EQUAL(33333, port);
    }

    TEST(RunAndPort) { // Тест 2.2
        UserInterface ui;
        char arg1[] = "vcalc_server";
        char arg2[] = "--run";
        char arg3[] = "-p";
        char arg4[] = "44444";
        char* argv[] = {arg1, arg2, arg3, arg4, nullptr};
        int argc = sizeof(argv) / sizeof(nullptr) - 1;
        bool result = ui.parseArgs(argc, argv);
        int port = ui.getParams().port;
        std::cout << "Тест 2.2: parseArgs=" << (result ? "true" : "false") 
                  << ", port=" << port << std::endl;
        REQUIRE CHECK(result);
        CHECK_EQUAL(44444, port);
    }

    TEST(AllParams) { // Тест 2.3
        UserInterface ui;
        char arg1[] = "vcalc_server";
        char arg2[] = "--run";
        char arg3[] = "-d";
        char arg4[] = "users.conf";
        char arg5[] = "-l";
        char arg6[] = "server.log";
        char arg7[] = "-p";
        char arg8[] = "55555";
        char* argv[] = {arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, nullptr};
        int argc = sizeof(argv) / sizeof(nullptr) - 1;
        bool result = ui.parseArgs(argc, argv);
        int port = ui.getParams().port;
        std::cout << "Тест 2.3: parseArgs=" << (result ? "true" : "false") 
                  << ", port=" << port << std::endl;
        REQUIRE CHECK(result);
        CHECK_EQUAL(55555, port);
    }

    TEST(PortAndDb) { // Тест 2.4
        UserInterface ui;
        char arg1[] = "vcalc_server";
        char arg2[] = "--run";
        char arg3[] = "-p";
        char arg4[] = "44444";
        char arg5[] = "-d";
        char arg6[] = "users.conf";
        char* argv[] = {arg1, arg2, arg3, arg4, arg5, arg6, nullptr};
        int argc = sizeof(argv) / sizeof(nullptr) - 1;
        bool result = ui.parseArgs(argc, argv);
        int port = ui.getParams().port;
        std::cout << "Тест 2.4: parseArgs=" << (result ? "true" : "false") 
                  << ", port=" << port << std::endl;
        REQUIRE CHECK(result);
        CHECK_EQUAL(44444, port);
    }
}

SUITE(ExceptionTest) {
    TEST(UnknownParam) { // Тест 3.1
        UserInterface ui;
        char arg1[] = "vcalc_server";
        char arg2[] = "--run";
        char arg3[] = "-x";
        char* argv[] = {arg1, arg2, arg3, nullptr};
        int argc = sizeof(argv) / sizeof(nullptr) - 1;
        try {
            ui.parseArgs(argc, argv);
            std::cout << "Тест 3.1: ОШИБКА - исключение не брошено!" << std::endl;
        } catch (const InterfaceError& e) {
            std::cout << "Тест 3.1: Исключение InterfaceError: " << e.what() << std::endl;
        }
        CHECK_THROW(ui.parseArgs(argc, argv), InterfaceError);
    }

    TEST(MissingPortValue) { // Тест 3.2
        UserInterface ui;
        char arg1[] = "vcalc_server";
        char arg2[] = "--run";
        char arg3[] = "-p";
        char* argv[] = {arg1, arg2, arg3, nullptr};
        int argc = sizeof(argv) / sizeof(nullptr) - 1;
        try {
            ui.parseArgs(argc, argv);
            std::cout << "Тест 3.2: ОШИБКА - исключение не брошено!" << std::endl;
        } catch (const InterfaceError& e) {
            std::cout << "Тест 3.2: Исключение InterfaceError: " << e.what() << std::endl;
        }
        CHECK_THROW(ui.parseArgs(argc, argv), InterfaceError);
    }
}
