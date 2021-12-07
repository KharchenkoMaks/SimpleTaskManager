//
// Created by Maksym Kharchenko on 02.12.2021.
//

#ifndef SIMPLETASKMANAGER_ADDSUBTASKSTATE_H
#define SIMPLETASKMANAGER_ADDSUBTASKSTATE_H

#include "states/abstract/WizardStateWithStateMachine.h"
#include "states/factory/WizardStatesFactory.h"
#include "WizardContext.h"

#include <memory>
#include <optional>

class AddSubTaskState : public WizardStateWithStateMachine {
public:
    AddSubTaskState(const std::shared_ptr<ConsoleStateMachine>& state_machine,
                    const std::shared_ptr<Controller>& controller,
                    const std::shared_ptr<WizardStatesFactory>& states_factory,
                    const std::shared_ptr<ConsolePrinter>& printer,
                    const std::shared_ptr<ConsoleReader>& reader);
public:
    std::optional<std::shared_ptr<WizardStateConsole>> Execute(std::shared_ptr<WizardContext> context) override;
private:
    void ShowAddedTaskId(const TaskId& task_id);
};


#endif //SIMPLETASKMANAGER_ADDSUBTASKSTATE_H
