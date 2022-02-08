//
// Created by Maksym Kharchenko on 23.11.2021.
//

#ifndef SIMPLETASKMANAGER_QUITSTATE_H
#define SIMPLETASKMANAGER_QUITSTATE_H

#include "State.h"
#include "user_interface/StateContext.h"
#include "view/user_interface/console_io/ConsolePrinter.h"
#include "view/user_interface/console_io/ConsoleReader.h"

#include <memory>
#include <string>

class QuitState : public State {
public:
    QuitState(StateType next_state,
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


#endif //SIMPLETASKMANAGER_QUITSTATE_H
