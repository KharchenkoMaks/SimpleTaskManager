//
// Created by Maksym Kharchenko on 23.11.2021.
//

#ifndef SIMPLETASKMANAGER_HELPSTATE_H
#define SIMPLETASKMANAGER_HELPSTATE_H

#include "abstract/WizardStateConsole.h"
#include "factory/WizardStatesFactory.h"

#include <string>
#include <memory>

class HelpState : public WizardStateConsole {
public:
    explicit HelpState(const std::shared_ptr<ConsolePrinter>& printer,
                       const std::shared_ptr<ConsoleReader>& reader);
public:
    std::optional<std::shared_ptr<IWizardState>> Execute(std::shared_ptr<WizardContext> context,
                                          std::shared_ptr<WizardStatesFactory> state_factory) override;
};


#endif //SIMPLETASKMANAGER_HELPSTATE_H
