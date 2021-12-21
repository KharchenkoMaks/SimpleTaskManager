//
// Created by Maksym Kharchenko on 21.12.2021.
//

#ifndef SIMPLETASKMANAGER_COMMANDFACTORY_H
#define SIMPLETASKMANAGER_COMMANDFACTORY_H

#include "view/commands/CommandInterface.h"
#include "WizardContext.h"

#include <memory>

class CommandFactory {
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
};


#endif //SIMPLETASKMANAGER_COMMANDFACTORY_H
