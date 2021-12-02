//
// Created by Maksym Kharchenko on 02.12.2021.
//

#ifndef SIMPLETASKMANAGER_DELETETASKSTATE_H
#define SIMPLETASKMANAGER_DELETETASKSTATE_H

#include "states/abstract/WizardStateController.h"
#include "states/factory/WizardStatesFactory.h"
#include "WizardContext.h"
#include "tasks/Task.h"
#include "TaskId.h"

#include <memory>
#include <optional>

class DeleteTaskState : public WizardStateController {
public:
    DeleteTaskState(const std::shared_ptr<Controller>& controller,
                    const std::shared_ptr<WizardStatesFactory>& states_factory,
                    const std::shared_ptr<ConsolePrinter>& printer,
                    const std::shared_ptr<ConsoleReader>& reader);
public:
    std::optional<std::shared_ptr<WizardStateConsole>> Execute(std::shared_ptr<WizardContext> context) override;
};


#endif //SIMPLETASKMANAGER_DELETETASKSTATE_H
