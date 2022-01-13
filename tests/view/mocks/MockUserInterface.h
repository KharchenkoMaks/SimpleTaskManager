//
// Created by Maksym Kharchenko on 13.01.2022.
//

#ifndef SIMPLETASKMANAGER_MOCKUSERINTERFACE_H
#define SIMPLETASKMANAGER_MOCKUSERINTERFACE_H

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "view/user_interface/UserInterface.h"

class MockUserInterface : public UserInterface {
public:
    MockUserInterface() : UserInterface(nullptr) {}

    MOCK_METHOD(std::shared_ptr<CommandInterface>, AskUserForAction, (), (override));
    MOCK_METHOD(void, PrintAddedTaskId, (const TaskId& task_id), (override));
    MOCK_METHOD(void, PrintRequestResult, (ControllerRequestResult action_result), (override));
    MOCK_METHOD(void, ShowTasks, (const std::vector<TaskTransfer>& tasks), (override));
};

#endif //SIMPLETASKMANAGER_MOCKUSERINTERFACE_H
