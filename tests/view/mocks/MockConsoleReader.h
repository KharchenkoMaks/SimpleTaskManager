//
// Created by Maksym Kharchenko on 03.12.2021.
//

#ifndef SIMPLETASKMANAGER_MOCKCONSOLEREADER_H
#define SIMPLETASKMANAGER_MOCKCONSOLEREADER_H

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "user_interface/console_io/ConsoleReader.h"

class MockConsoleReader : public ConsoleReader {
public:
    MOCK_METHOD(std::string, ReadLine, (), (const, override));
};

#endif //SIMPLETASKMANAGER_MOCKCONSOLEREADER_H
