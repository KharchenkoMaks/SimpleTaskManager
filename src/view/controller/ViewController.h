//
// Created by Maksym Kharchenko on 21.12.2021.
//

#ifndef SIMPLETASKMANAGER_VIEWCONTROLLER_H
#define SIMPLETASKMANAGER_VIEWCONTROLLER_H

#include "commands/factory/CommandFactory.h"
#include "states/factory/StatesFactory.h"
#include "ConsoleStateMachine.h"

#include <memory>

class ViewController {
public:
    ViewController(std::unique_ptr<ConsoleStateMachine> state_machine,
                   std::unique_ptr<CommandFactory> command_factory,
                   std::unique_ptr<StatesFactory> states_factory);
public:
    void RunUserInterface();
private:
    std::shared_ptr<CommandFactory> command_factory_;
    std::shared_ptr<StatesFactory> states_factory_;

    std::shared_ptr<ConsoleStateMachine> state_machine_;
};


#endif //SIMPLETASKMANAGER_VIEWCONTROLLER_H
