//
// Created by Maksym Kharchenko on 07.02.2022.
//

#ifndef SIMPLETASKMANAGER_PROGRAMOPTIONSPARSERS_H
#define SIMPLETASKMANAGER_PROGRAMOPTIONSPARSERS_H

#include <string>

std::string parse_options_host(int argc, char* argv[], const std::string& default_host, const std::string& default_port);


#endif //SIMPLETASKMANAGER_PROGRAMOPTIONSPARSERS_H
