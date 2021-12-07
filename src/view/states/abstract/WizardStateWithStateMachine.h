//
// Created by Maksym Kharchenko on 07.12.2021.
//

#ifndef SIMPLETASKMANAGER_WIZARDSTATEWITHSTATEMACHINE_H
#define SIMPLETASKMANAGER_WIZARDSTATEWITHSTATEMACHINE_H

#include "WizardStateController.h"
#include "WizardContext.h"

#include <optional>
#include <memory>

class ConsoleStateMachine;

class WizardStateWithStateMachine : public WizardStateController {
public:
    WizardStateWithStateMachine(const std::shared_ptr<ConsoleStateMachine>& state_machine,
                                const std::shared_ptr<Controller>& controller,
                                const std::shared_ptr<WizardStatesFactory>& states_factory,
                                const std::shared_ptr<ConsolePrinter>& printer,
                                const std::shared_ptr<ConsoleReader>& reader);
public:
    void RunStateMachine(const std::shared_ptr<WizardContext>& context,
                                                   const std::optional<std::shared_ptr<WizardStateConsole>>& initial_state);
private:
    std::shared_ptr<ConsoleStateMachine> state_machine_;
};


#endif //SIMPLETASKMANAGER_WIZARDSTATEWITHSTATEMACHINE_H
