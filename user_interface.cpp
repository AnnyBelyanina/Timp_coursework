/** @file
 * @author Белянина А.А.
 * @version 1.0
 * @date 22.11.2026
 * @copyright ИБСТ ПГУ
 * @warning Это учебный пример
 * @brief Реализация модуля пользовательского интерфейса
 */
 
#include "user_interface.h"
#include "errors.h"
#include <boost/program_options.hpp>
#include <iostream>

namespace po = boost::program_options;

UserInterface::UserInterface(){
    // инициализация параметров программы значениями по умолчанию
    params.databaseFile = "./vcalc.conf";
    params.logFile = "./vcalc.log";
    params.port = 33333;
}

bool UserInterface::parseArgs(int argc, char* argv[]){
    // описание допустимых параметров командной строки
    po::options_description desc("Параметры сервера vcalc"); 
    
    desc.add_options()
        ("help,h", "Вывод справки")
        ("run", "Запуск сервера (обязательный параметр)")
        ("db-file,d", po::value<std::string>(&params.databaseFile)->default_value("./vcalc.conf"), 
         "Имя файла с базой клиентов") 
        ("log-file,l", po::value<std::string>(&params.logFile)->default_value("./vcalc.log"), 
         "Имя файла с журналом работы") 
        ("port,p", po::value<int>(&params.port)->default_value(33333),
         "Номер порта сервера");
    
    po::variables_map vm;
    
    try{
        // парсинг командной строки
        po::store(po::parse_command_line(argc, argv, desc), vm);
        
        // обработка запроса справки или отсутствия обязательного параметра --run
        if (vm.count("help") || !vm.count("run")){
            showHelp();
            return false;
        }
        
        // присвоение значений по умолчанию и возбуждение исключений при ошибках
        po::notify(vm);
        
    } catch (po::error& e){
        // перехват ошибок парсинга и преобразование их в исключение интерфейса
        std::cerr << "Ошибка параметров: " << e.what() << std::endl;
        std::cerr << "Используйте -h для получения справки" << std::endl;
        throw InterfaceError(std::string(e.what()));
    }
    
    return true;
}

void UserInterface::showHelp(){
    // вывод форматированной справки по использованию программы
    std::cout << "Сервер vcalc - серверная программа для клиент-серверной системы обработки данных\n"
              << "\n"
              << "Использование: vcalc_server --run [options]\n"
              << "\n"
              << "Параметры:\n"
              << "  -h [ --help ]         Вывод справки\n"
              << "  -d [ --db-file ] arg  Имя файла с базой клиентов (по умолчанию ./vcalc.conf)\n"
              << "  -l [ --log-file ] arg Имя файла с журналом работы (по умолчанию ./vcalc.log)\n"
              << "  -p [ --port ] arg     Номер порта сервера (по умолчанию 33333)\n"
              << std::endl;
}

ServerParams UserInterface::getParams() const {  
    // возврат структуры с текущими параметрами программы
    return params;
}
