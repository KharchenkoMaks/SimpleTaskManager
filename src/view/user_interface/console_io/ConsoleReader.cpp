//
// Created by Maksym Kharchenko on 26.11.2021.
//

#include "ConsoleReader.h"

std::string ConsoleReader::ReadLine() const {
    std::string line;
    std::getline(std::cin, line);
    return line;
}
