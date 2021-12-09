//
// Created by Maksym Kharchenko on 09.12.2021.
//

#ifndef SIMPLETASKMANAGER_ENDSTATE_H
#define SIMPLETASKMANAGER_ENDSTATE_H

#include "states/abstract/WizardStateConsole.h"
#include "states/factory/WizardStatesFactory.h"
#include "WizardContext.h"

#include <memory>
#include <string>

class EndState : public WizardStateConsole {
public:
    EndState(const std::shared_ptr<WizardStatesFactory>& states_factory,
                       const std::shared_ptr<ConsolePrinter>& printer,
                       const std::shared_ptr<ConsoleReader>& reader);
public:
    std::shared_ptr<WizardStateConsole> Execute(std::shared_ptr<WizardContext> context) override;
};


#endif //SIMPLETASKMANAGER_ENDSTATE_H
