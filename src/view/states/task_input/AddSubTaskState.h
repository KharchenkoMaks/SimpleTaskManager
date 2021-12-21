//
// Created by Maksym Kharchenko on 02.12.2021.
//

#ifndef SIMPLETASKMANAGER_ADDSUBTASKSTATE_H
#define SIMPLETASKMANAGER_ADDSUBTASKSTATE_H

#include "states/StateInterface.h"
#include "states/factory/StatesFactory.h"
#include "StateContext.h"

#include <memory>
#include <optional>

class AddSubTaskState : public StateInterface {
public:
    AddSubTaskState(const std::shared_ptr<StatesFactory>& factory);
public:
    std::shared_ptr<StateInterface> Execute(std::shared_ptr<StateContext> context) override;
private:
    void ShowAddedTaskId(const TaskId& task_id);

    std::pair<TaskActionResult, std::optional<TaskId>> GiveSubTaskToController(const TaskId& parent_id, const std::shared_ptr<StateContext>& context_with_added_task);
    std::shared_ptr<StateInterface> PrintResultAndChangeState(const std::pair<TaskActionResult, std::optional<TaskId>>& added_subtask_result);
private:
    std::weak_ptr<StatesFactory> factory_;
};


#endif //SIMPLETASKMANAGER_ADDSUBTASKSTATE_H
