//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "ConsoleMultiFunctionalPrinter.h"

void ConsoleMultiFunctionalPrinter::Write(const std::string &message) {
    std::cout << message;
}

void ConsoleMultiFunctionalPrinter::WriteLine(const std::string &message) {
    Write(message + "\n");
}

void ConsoleMultiFunctionalPrinter::WriteError(const std::string &message) {
    WriteLine("[Error]: " + message);
}

std::string ConsoleMultiFunctionalPrinter::ReadLine() {
    std::string line;
    std::cin >> line;
    return line;
}
