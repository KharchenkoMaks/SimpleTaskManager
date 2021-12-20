//
// Created by Maksym Kharchenko on 26.11.2021.
//

#ifndef SIMPLETASKMANAGER_CONSOLEREADER_H
#define SIMPLETASKMANAGER_CONSOLEREADER_H

#include <iostream>
#include <string>

class ConsoleReader {
public:
    virtual std::string ReadLine() const;
public:
    virtual ~ConsoleReader() = default;
};


#endif //SIMPLETASKMANAGER_CONSOLEREADER_H
