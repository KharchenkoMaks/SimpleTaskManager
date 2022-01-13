//
// Created by Maksym Kharchenko on 13.01.2022.
//

#ifndef SIMPLETASKMANAGER_MOCKCOMMAND_H
#define SIMPLETASKMANAGER_MOCKCOMMAND_H

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "view/commands/CommandInterface.h"

class MockCommand : public CommandInterface {
public:
    MOCK_METHOD(CommandResult, Execute, (const std::shared_ptr<Controller>& controller), (override));
};

#endif //SIMPLETASKMANAGER_MOCKCOMMAND_H
