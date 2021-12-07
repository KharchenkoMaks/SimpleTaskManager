//
// Created by Maksym Kharchenko on 07.12.2021.
//

#ifndef SIMPLETASKMANAGER_MOCKCONSOLESTATEMACHINE_H
#define SIMPLETASKMANAGER_MOCKCONSOLESTATEMACHINE_H

#include "ConsoleStateMachine.h"

class MockConsoleStateMachine : public ConsoleStateMachine {
public:
    MOCK_METHOD(std::shared_ptr<WizardContext>,
                Run,
                (const std::shared_ptr<WizardContext>& context, const std::optional<std::shared_ptr<WizardStateConsole>>& initial_state),
                (override));
};

#endif //SIMPLETASKMANAGER_MOCKCONSOLESTATEMACHINE_H
