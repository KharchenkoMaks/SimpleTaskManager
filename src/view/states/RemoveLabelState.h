//
// Created by Maksym Kharchenko on 17.01.2022.
//

#ifndef SIMPLETASKMANAGER_REMOVELABELSTATE_H
#define SIMPLETASKMANAGER_REMOVELABELSTATE_H

#include "states/State.h"
#include "view/commands/factory/CommandFactory.h"
#include "user_interface/StateContext.h"
#include "view/user_interface/console_io/ConsolePrinter.h"
#include "view/user_interface/console_io/ConsoleReader.h"

#include <memory>
#include <optional>

class RemoveLabelState : public State {
public:
    RemoveLabelState(StateType next_state,
                     StateType error_state,
                     const std::shared_ptr<ConsolePrinter>& printer,
                     const std::shared_ptr<ConsoleReader>& reader,
                     const std::shared_ptr<CommandFactory>& command_factory);
public:
    StateType Execute(StateContext& context) override;
private:
    StateType next_state_;
    StateType error_state_;
    std::shared_ptr<ConsolePrinter> printer_;
    std::shared_ptr<ConsoleReader> reader_;
    std::shared_ptr<CommandFactory> command_factory_;
};


#endif //SIMPLETASKMANAGER_REMOVELABELSTATE_H
