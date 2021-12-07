//
// Created by Maksym Kharchenko on 25.11.2021.
//

#ifndef SIMPLETASKMANAGER_EDITTASKSTATE_H
#define SIMPLETASKMANAGER_EDITTASKSTATE_H

#include "states/abstract/WizardStateWithStateMachine.h"
#include "states/factory/WizardStatesFactory.h"
#include "WizardContext.h"
#include "tasks/Task.h"
#include "id/TaskId.h"

#include <memory>
#include <optional>

class EditTaskState : public WizardStateWithStateMachine {
public:
    EditTaskState(const std::shared_ptr<ConsoleStateMachine>& state_machine,
                  const std::shared_ptr<Controller>& controller,
                  const std::shared_ptr<WizardStatesFactory>& states_factory,
                  const std::shared_ptr<ConsolePrinter>& printer,
                  const std::shared_ptr<ConsoleReader>& reader);
public:
    std::optional<std::shared_ptr<WizardStateConsole>> Execute(std::shared_ptr<WizardContext> context) override;
};


#endif //SIMPLETASKMANAGER_EDITTASKSTATE_H
