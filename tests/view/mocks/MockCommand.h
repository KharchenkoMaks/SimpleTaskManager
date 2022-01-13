//
// Created by Maksym Kharchenko on 13.01.2022.
//

#ifndef SIMPLETASKMANAGER_MOCKCOMMAND_H
#define SIMPLETASKMANAGER_MOCKCOMMAND_H

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "view/commands/Command.h"

class MockCommand : public Command {
public:
    MOCK_METHOD(CommandResult, Execute, (const std::shared_ptr<Controller>& controller), (override));
};

#endif //SIMPLETASKMANAGER_MOCKCOMMAND_H
