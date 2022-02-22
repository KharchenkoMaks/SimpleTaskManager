//
// Created by Maksym Kharchenko on 02.12.2021.
//

#ifndef SIMPLETASKMANAGER_ADDSUBTASKSTATE_H
#define SIMPLETASKMANAGER_ADDSUBTASKSTATE_H

#include "states/State.h"
#include "view/commands/factory/CommandFactory.h"
#include "user_interface/StateContext.h"
#include "view/user_interface/console_io/ConsolePrinter.h"
#include "view/user_interface/console_io/ConsoleReader.h"
#include "view/user_interface/ConsoleStateMachine.h"

#include <memory>
#include <optional>

class AddSubTaskState : public State {
public:
    AddSubTaskState(StateType next_state,
                    StateType error_state,
                    const std::shared_ptr<ConsolePrinter>& printer,
                    const std::shared_ptr<ConsoleReader>& reader,
                    const std::shared_ptr<CommandFactory>& command_factory,
                    std::unique_ptr<ConsoleStateMachine> state_machine);
public:
    StateType Execute(StateContext& context) override;
private:
    StateType next_state_;
    StateType error_state_;
    std::shared_ptr<ConsolePrinter> printer_;
    std::shared_ptr<ConsoleReader> reader_;
    std::shared_ptr<CommandFactory> command_factory_;
    std::unique_ptr<ConsoleStateMachine> state_machine_;
};


#endif //SIMPLETASKMANAGER_ADDSUBTASKSTATE_H
