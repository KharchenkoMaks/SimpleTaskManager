//
// Created by Maksym Kharchenko on 16.12.2021.
//

#ifndef SIMPLETASKMANAGER_LOADSTATE_H
#define SIMPLETASKMANAGER_LOADSTATE_H

#include "states/State.h"
#include "view/commands/factory/CommandFactory.h"
#include "user_interface/StateContext.h"
#include "Task.pb.h"
#include "view/user_interface/console_io/ConsolePrinter.h"
#include "view/user_interface/console_io/ConsoleReader.h"

#include <memory>
#include <optional>

class LoadState : public State {
public:
    LoadState(StateType next_state,
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


#endif //SIMPLETASKMANAGER_LOADSTATE_H
