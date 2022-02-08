//
// Created by Maksym Kharchenko on 23.11.2021.
//

#ifndef SIMPLETASKMANAGER_ROOTSTATE_H
#define SIMPLETASKMANAGER_ROOTSTATE_H

#include "State.h"
#include "user_interface/StateContext.h"
#include "view/user_interface/console_io/ConsolePrinter.h"
#include "view/user_interface/console_io/ConsoleReader.h"

#include <string>
#include <memory>

class RootState : public State {
public:
    RootState(StateType error_state,
              const std::shared_ptr<ConsolePrinter>& printer,
              const std::shared_ptr<ConsoleReader>& reader);
public:
    StateType Execute(StateContext& context) override;
private:
    StateType GetStateTypeByUserCommand(const std::string& command);
private:
    StateType error_state_;
    std::shared_ptr<ConsolePrinter> printer_;
    std::shared_ptr<ConsoleReader> reader_;
};


#endif //SIMPLETASKMANAGER_ROOTSTATE_H
