//
// Created by Maksym Kharchenko on 24.11.2021.
//

#ifndef SIMPLETASKMANAGER_INPUTTASKTITLESTATE_H
#define SIMPLETASKMANAGER_INPUTTASKTITLESTATE_H

#include "states/State.h"
#include "user_interface/StateContext.h"
#include "view/user_interface/console_io/ConsolePrinter.h"
#include "view/user_interface/console_io/ConsoleReader.h"

#include <string>
#include <memory>

class InputTaskTitleState : public State {
public:
    InputTaskTitleState(StateType next_state,
                        const std::shared_ptr<ConsolePrinter>& printer,
                        const std::shared_ptr<ConsoleReader>& reader);
public:
    StateType Execute(StateContext& context) override;
private:
    StateType next_state_;
    std::shared_ptr<ConsolePrinter> printer_;
    std::shared_ptr<ConsoleReader> reader_;
};


#endif //SIMPLETASKMANAGER_INPUTTASKTITLESTATE_H
