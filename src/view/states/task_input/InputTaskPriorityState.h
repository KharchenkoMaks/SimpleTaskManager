//
// Created by Maksym Kharchenko on 24.11.2021.
//

#ifndef SIMPLETASKMANAGER_INPUTTASKPRIORITYSTATE_H
#define SIMPLETASKMANAGER_INPUTTASKPRIORITYSTATE_H

#include "states/State.h"
#include "user_interface/StateContext.h"
#include "view/user_interface/console_io/ConsolePrinter.h"
#include "view/user_interface/console_io/ConsoleReader.h"

#include <string>
#include <memory>

class InputTaskPriorityState : public State {
public:
    InputTaskPriorityState(StateType next_state,
                           StateType error_state,
                           const std::shared_ptr<ConsolePrinter>& printer,
                           const std::shared_ptr<ConsoleReader>& reader);
public:
    StateType Execute(StateContext& context) override;
private:
    StateType next_state_;
    StateType error_state_;
    std::shared_ptr<ConsolePrinter> printer_;
    std::shared_ptr<ConsoleReader> reader_;
};


#endif //SIMPLETASKMANAGER_INPUTTASKPRIORITYSTATE_H
