//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "console_io/ConsolePrinter.h"

void ConsolePrinter::Write(const std::string &message) {
    std::cout << message;
}

void ConsolePrinter::WriteLine(const std::string &message) {
    Write(message + "\n");
}

void ConsolePrinter::WriteError(const std::string &message) {
    WriteLine("[Error]: " + message);
}