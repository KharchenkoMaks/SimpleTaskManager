//
// Created by Maksym Kharchenko on 01.12.2021.
//

#ifndef SIMPLETASKMANAGER_COMPLETETASKSTATE_H
#define SIMPLETASKMANAGER_COMPLETETASKSTATE_H

#include "states/abstract/WizardStateController.h"
#include "states/factory/WizardStatesFactory.h"
#include "WizardContext.h"
#include "tasks/Task.h"
#include "id/TaskId.h"

#include <memory>
#include <optional>

class CompleteTaskState : public WizardStateController {
public:
    CompleteTaskState(const std::shared_ptr<Controller>& controller,
                  const std::shared_ptr<WizardStatesFactory>& states_factory,
                  const std::shared_ptr<ConsolePrinter>& printer,
                  const std::shared_ptr<ConsoleReader>& reader);
public:
    std::optional<std::shared_ptr<WizardStateConsole>> Execute(std::shared_ptr<WizardContext> context) override;
};


#endif //SIMPLETASKMANAGER_COMPLETETASKSTATE_H
