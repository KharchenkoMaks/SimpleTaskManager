//
// Created by Maksym Kharchenko on 23.11.2021.
//

#ifndef SIMPLETASKMANAGER_CONSOLEPRINTER_H
#define SIMPLETASKMANAGER_CONSOLEPRINTER_H

#include <iostream>
#include <string>

class ConsolePrinter {
public:
    void Write(const std::string& message);
    void WriteLine(const std::string& message);
    void WriteError(const std::string& message);

    std::string ReadLine();
};


#endif //SIMPLETASKMANAGER_CONSOLEPRINTER_H
