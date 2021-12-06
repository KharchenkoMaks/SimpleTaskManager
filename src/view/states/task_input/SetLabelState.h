//
// Created by Maksym Kharchenko on 06.12.2021.
//

#ifndef SIMPLETASKMANAGER_SETLABELSTATE_H
#define SIMPLETASKMANAGER_SETLABELSTATE_H

#include "states/abstract/WizardStateController.h"
#include "states/factory/WizardStatesFactory.h"
#include "WizardContext.h"

#include <memory>
#include <optional>

class SetLabelState : public WizardStateController {
public:
    SetLabelState(const std::shared_ptr<Controller>& controller,
                    const std::shared_ptr<WizardStatesFactory>& states_factory,
                    const std::shared_ptr<ConsolePrinter>& printer,
                    const std::shared_ptr<ConsoleReader>& reader);
public:
    std::optional<std::shared_ptr<WizardStateConsole>> Execute(std::shared_ptr<WizardContext> context) override;
};


#endif //SIMPLETASKMANAGER_SETLABELSTATE_H
