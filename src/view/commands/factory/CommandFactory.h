//
// Created by Maksym Kharchenko on 21.12.2021.
//

#ifndef SIMPLETASKMANAGER_COMMANDFACTORY_H
#define SIMPLETASKMANAGER_COMMANDFACTORY_H

#include "view/commands/CommandInterface.h"
#include "controller/Controller.h"
#include "WizardContext.h"

#include <memory>
#include <optional>

class CommandFactory {
public:
    explicit CommandFactory(std::unique_ptr<Controller> controller);
public:
    std::unique_ptr<CommandInterface> CreateAddTaskCommand(const WizardContext& context);
    std::unique_ptr<CommandInterface> CreateAddSubTaskCommand(const WizardContext& context);
    std::unique_ptr<CommandInterface> CreateEditCommand(const WizardContext& context);
    std::unique_ptr<CommandInterface> CreateCompleteCommand(const WizardContext& context);
    std::unique_ptr<CommandInterface> CreateDeleteCommand(const WizardContext& context);
    std::unique_ptr<CommandInterface> CreateSetLabelCommand(const WizardContext& context);
    std::unique_ptr<CommandInterface> CreateShowCommand(const WizardContext& context);
    std::unique_ptr<CommandInterface> CreateSaveCommand(const WizardContext& context);
    std::unique_ptr<CommandInterface> CreateLoadCommand(const WizardContext& context);
private:
    std::shared_ptr<Controller> controller_;
};


#endif //SIMPLETASKMANAGER_COMMANDFACTORY_H
