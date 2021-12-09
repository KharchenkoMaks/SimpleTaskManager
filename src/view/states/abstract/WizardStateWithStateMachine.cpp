//
// Created by Maksym Kharchenko on 07.12.2021.
//

#include "WizardStateWithStateMachine.h"
#include "ConsoleStateMachine.h"

WizardStateWithStateMachine::WizardStateWithStateMachine(const std::shared_ptr<ConsoleStateMachine>& state_machine,
                                                         const std::shared_ptr<Controller>& controller,
                                                         const std::shared_ptr<WizardStatesFactory>& states_factory,
                                                         const std::shared_ptr<ConsolePrinter>& printer,
                                                         const std::shared_ptr<ConsoleReader>& reader) :
                                                         WizardStateController(controller,
                                                                               states_factory,
                                                                               printer,
                                                                               reader),
                                                         state_machine_(state_machine) {

}

std::shared_ptr<WizardContext> WizardStateWithStateMachine::RunStateMachine(const std::shared_ptr<WizardContext>& context,
                                                     const std::shared_ptr<WizardStateConsole>& initial_state) {
    return state_machine_->Run(context, initial_state);
}
