#include "user_interface.h"
#include "errors.h"
#include <boost/program_options.hpp>
#include <iostream>

namespace po = boost::program_options;

UserInterface::UserInterface(){
    params.databaseFile = "./vcalc.conf";
    params.logFile = "./vcalc.log";
    params.port = 33333;
}

bool UserInterface::parseArgs(int argc, char* argv[]){
    po::options_description desc("Параметры сервера vcalc"); 
    
    desc.add_options()
        ("help,h", "Вывод справки")
        ("db-file,d", po::value<std::string>(&params.databaseFile)->default_value("./vcalc.conf"), 
         "Имя файла с базой клиентов") 
        ("log-file,l", po::value<std::string>(&params.logFile)->default_value("./vcalc.log"), 
         "Имя файла с журналом работы") 
        ("port,p", po::value<int>(&params.port)->default_value(33333),
         "Номер порта сервера");
    
    po::variables_map vm;
    
    try{
        po::store(po::parse_command_line(argc, argv, desc), vm);
        
        if (vm.count("help") || argc == 1){
            showHelp();
            return false;
        }
        
        po::notify(vm);
        
    } catch (po::error& e){
        std::cerr << "Ошибка параметров: " << e.what() << std::endl;
        std::cerr << "Используйте -h для получения справки" << std::endl;
        throw InterfaceError(std::string(e.what()));
    }
    
    return true;
}

void UserInterface::showHelp(){
    std::cout << "Сервер vcalc - серверная программа для клиент-серверной системы обработки данных\n"
              << "\n"
              << "Использование: vcalc_server [options]\n"
              << "\n"
              << "Параметры:\n"
              << "  -h [ --help ]         Вывод справки\n"
              << "  -d [ --db-file ] arg  Имя файла с базой клиентов (по умолчанию ./vcalc.conf)\n"
              << "  -l [ --log-file ] arg Имя файла с журналом работы (по умолчанию ./vcalc.log)\n"
              << "  -p [ --port ] arg     Номер порта сервера (по умолчанию 33333)\n"
              << std::endl;
}

ServerParams UserInterface::getParams() const {  
    return params;
}
