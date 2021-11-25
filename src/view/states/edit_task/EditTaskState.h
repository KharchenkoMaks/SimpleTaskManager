//
// Created by Maksym Kharchenko on 25.11.2021.
//

#ifndef SIMPLETASKMANAGER_EDITTASKSTATE_H
#define SIMPLETASKMANAGER_EDITTASKSTATE_H

#include "states/abstract/WizardStatePrinter.h"
#include "states/factory/WizardStatesFactory.h"
#include "context/WizardContext.h"
#include "tasks/Task.h"
#include "TaskId.h"

#include <memory>

class EditTaskState : public WizardStatePrinter {
public:
    explicit EditTaskState(std::shared_ptr<ConsolePrinter> printer);
public:
    std::shared_ptr<IWizardState> Execute(std::shared_ptr<WizardContext> context,
                                          std::shared_ptr<WizardStatesFactory> state_factory) override;
private:
    std::string InputTaskIdToEdit();
    std::shared_ptr<WizardContext> RunStateMachineToEditTask(const Task& task_to_edit);
};


#endif //SIMPLETASKMANAGER_EDITTASKSTATE_H
