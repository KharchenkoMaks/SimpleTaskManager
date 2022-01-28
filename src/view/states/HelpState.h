//
// Created by Maksym Kharchenko on 23.11.2021.
//

#ifndef SIMPLETASKMANAGER_HELPSTATE_H
#define SIMPLETASKMANAGER_HELPSTATE_H

#include "State.h"
#include "view/user_interface/console_io/ConsolePrinter.h"

#include <string>
#include <memory>

class HelpState : public State {
public:
    HelpState(StateType next_state,
              const std::shared_ptr<ConsolePrinter>& printer);
public:
    StateType Execute(StateContext& context) override;
private:
    StateType next_state_;
    std::shared_ptr<ConsolePrinter> printer_;
};


#endif //SIMPLETASKMANAGER_HELPSTATE_H
