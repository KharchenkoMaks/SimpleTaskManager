//
// Created by Maksym Kharchenko on 02.12.2021.
//

#ifndef SIMPLETASKMANAGER_ADDSUBTASKSTATE_H
#define SIMPLETASKMANAGER_ADDSUBTASKSTATE_H

#include "states/abstract/WizardStateInterface.h"
#include "states/factory/WizardStatesFactory.h"
#include "WizardContext.h"

#include <memory>
#include <optional>

class AddSubTaskState : public WizardStateInterface {
public:
    AddSubTaskState(const std::shared_ptr<WizardStatesFactory>& factory);
public:
    std::shared_ptr<WizardStateInterface> Execute(std::shared_ptr<WizardContext> context) override;
private:
    void ShowAddedTaskId(const TaskId& task_id);

    std::pair<TaskActionResult, std::optional<TaskId>> GiveSubTaskToController(const TaskId& parent_id, const std::shared_ptr<WizardContext>& context_with_added_task);
    std::shared_ptr<WizardStateInterface> PrintResultAndChangeState(const std::pair<TaskActionResult, std::optional<TaskId>>& added_subtask_result);
private:
    std::weak_ptr<WizardStatesFactory> factory_;
};


#endif //SIMPLETASKMANAGER_ADDSUBTASKSTATE_H
