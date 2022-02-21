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
    void PrintTaskWithChildren(const std::vector<RelationalTask>& tasks, const RelationalTask& task_to_print, const std::string& prefix) const;
private:
    StateType next_state_;
    std::shared_ptr<ConsolePrinter> printer_;
};


#endif //SIMPLETASKMANAGER_SHOWSTATE_H
