//
// Created by Maksym Kharchenko on 03.12.2021.
//

#ifndef SIMPLETASKMANAGER_MOCKCONSOLEPRINTER_H
#define SIMPLETASKMANAGER_MOCKCONSOLEPRINTER_H

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "console_io/ConsolePrinter.h"

class MockConsolePrinter : public ConsolePrinter {
public:
    MOCK_METHOD(void, Write, (const std::string& message), (override));
    MOCK_METHOD(void, WriteLine, (const std::string& message), (override));
    MOCK_METHOD(void, WriteError, (const std::string& message), (override));
};

#endif //SIMPLETASKMANAGER_MOCKCONSOLEPRINTER_H
