//
// Created by Maksym Kharchenko on 24.12.2021.
//

#ifndef SIMPLETASKMANAGER_SHOWSTATE_H
#define SIMPLETASKMANAGER_SHOWSTATE_H

#include "Task.pb.h"
#include "State.h"
#include "view/user_interface/console_io/ConsolePrinter.h"

#include <vector>

class ShowState : public State {
public:
    ShowState(StateType next_state,
              const std::shared_ptr<ConsolePrinter>& printer);
public:
    StateType Execute(StateContext& context) override;
private:
    void PrintTasks(const std::vector<RelationalTask>& tasks);
private:
    StateType next_state_;
    std::shared_ptr<ConsolePrinter> printer_;
};


#endif //SIMPLETASKMANAGER_SHOWSTATE_H
