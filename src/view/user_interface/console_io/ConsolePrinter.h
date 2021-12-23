//
// Created by Maksym Kharchenko on 23.11.2021.
//

#ifndef SIMPLETASKMANAGER_CONSOLEPRINTER_H
#define SIMPLETASKMANAGER_CONSOLEPRINTER_H

#include <iostream>
#include <string>

class ConsolePrinter {
public:
    virtual void Write(const std::string& message) const;
    virtual void WriteLine(const std::string& message) const;
    virtual void WriteError(const std::string& message) const;
    
    virtual ~ConsolePrinter() = default;
};


#endif //SIMPLETASKMANAGER_CONSOLEPRINTER_H
