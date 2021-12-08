//
// Created by Maksym Kharchenko on 30.11.2021.
//

#include "WizardStateController.h"

WizardStateController::WizardStateController(const std::shared_ptr<Controller> &controller,
                                             const std::shared_ptr<WizardStatesFactory> &states_factory,
                                             const std::shared_ptr<ConsolePrinter> &printer,
                                             const std::shared_ptr<ConsoleReader> &reader) :
                                             WizardStateConsole(states_factory, printer, reader),
                                             controller_(controller) {

}

std::shared_ptr<Controller> WizardStateController::GetController() const {
    return controller_;
}
