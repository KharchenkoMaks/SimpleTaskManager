//
// Created by Maksym Kharchenko on 30.11.2021.
//

#ifndef SIMPLETASKMANAGER_WIZARDSTATECONTROLLER_H
#define SIMPLETASKMANAGER_WIZARDSTATECONTROLLER_H

#include "WizardStateConsole.h"
#include "Controller.h"

#include <memory>

class WizardStateController : public WizardStateConsole {
public:
    WizardStateController(const std::shared_ptr<Controller>& controller,
                          const std::shared_ptr<WizardStatesFactory> &states_factory,
                          const std::shared_ptr<ConsolePrinter> &printer,
                          const std::shared_ptr<ConsoleReader> &reader);

public:
    std::shared_ptr<Controller> GetController() const;

private:
    std::shared_ptr<Controller> controller_;
};


#endif //SIMPLETASKMANAGER_WIZARDSTATECONTROLLER_H
