//
// Created by Maksym Kharchenko on 21.01.2022.
//

#ifndef SIMPLETASKMANAGER_INPUTSHOWBYLABELSTATE_H
#define SIMPLETASKMANAGER_INPUTSHOWBYLABELSTATE_H

#include "states/State.h"
#include "user_interface/StateContext.h"
#include "Task.pb.h"
#include "view/user_interface/console_io/ConsolePrinter.h"
#include "view/user_interface/console_io/ConsoleReader.h"

#include <memory>
#include <optional>

/* Getting task label from user
  * Used in InputShowParameters to get task label that will be used to sort tasks
  * */

class InputShowByLabelState : public State {
public:
    InputShowByLabelState(StateType next_state,
                          const std::shared_ptr<ConsolePrinter>& printer,
                          const std::shared_ptr<ConsoleReader>& reader);
public:
    StateType Execute(StateContext& context) override;
private:
    StateType next_state_;
    std::shared_ptr<ConsolePrinter> printer_;
    std::shared_ptr<ConsoleReader> reader_;
};


#endif //SIMPLETASKMANAGER_INPUTSHOWBYLABELSTATE_H
