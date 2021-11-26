//
// Created by Maksym Kharchenko on 26.11.2021.
//

#include "console_io/ConsoleReader.h"

std::string ConsoleReader::ReadLine() {
    std::string line;
    std::cin >> line;
    return line;
}
