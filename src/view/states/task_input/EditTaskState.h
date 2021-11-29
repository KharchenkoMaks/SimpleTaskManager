//
// Created by Maksym Kharchenko on 25.11.2021.
//

#ifndef SIMPLETASKMANAGER_EDITTASKSTATE_H
#define SIMPLETASKMANAGER_EDITTASKSTATE_H

#include "states/abstract/WizardStateConsole.h"
#include "states/factory/WizardStatesFactory.h"
#include "WizardContext.h"
#include "tasks/Task.h"
#include "TaskId.h"

#include <memory>

class EditTaskState : public WizardStateConsole {
public:
    explicit EditTaskState(const std::shared_ptr<WizardStatesFactory>& states_factory,
                           const std::shared_ptr<ConsolePrinter>& printer,
                           const std::shared_ptr<ConsoleReader>& reader);
public:
    std::optional<std::shared_ptr<IWizardState>> Execute(std::shared_ptr<WizardContext> context) override;
};


#endif //SIMPLETASKMANAGER_EDITTASKSTATE_H
