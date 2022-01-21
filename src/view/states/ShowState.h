//
// Created by Maksym Kharchenko on 24.12.2021.
//

#ifndef SIMPLETASKMANAGER_SHOWSTATE_H
#define SIMPLETASKMANAGER_SHOWSTATE_H

#include "Task.pb.h"
#include "State.h"
#include "factory/StatesFactory.h"

#include <vector>

class ShowState : public State {
public:
    explicit ShowState(const std::shared_ptr<StatesFactory>& factory);
public:
    std::shared_ptr<State> Execute(StateContext& context) override;
private:
    void PrintTasks(const CommandResult::TasksToShow& tasks_to_show);
private:
    std::weak_ptr<StatesFactory> factory_;
};


#endif //SIMPLETASKMANAGER_SHOWSTATE_H
