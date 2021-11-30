//
// Created by Maksym Kharchenko on 23.11.2021.
//

#ifndef SIMPLETASKMANAGER_ROOTSTATE_H
#define SIMPLETASKMANAGER_ROOTSTATE_H

#include "abstract/WizardStateConsole.h"
#include "factory/WizardStatesFactory.h"
#include "WizardContext.h"

#include <string>
#include <memory>

class RootState : public WizardStateConsole {
public:
    explicit RootState(const std::shared_ptr<WizardStatesFactory>& states_factory,
                       const std::shared_ptr<ConsolePrinter>& printer,
                       const std::shared_ptr<ConsoleReader>& reader);
public:
    std::optional<std::shared_ptr<WizardStateConsole>> Execute(std::shared_ptr<WizardContext> context) override;
};


#endif //SIMPLETASKMANAGER_ROOTSTATE_H
