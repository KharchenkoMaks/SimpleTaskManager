//
// Created by Maksym Kharchenko on 30.11.2021.
//

#include "ShowState.h"

ShowState::ShowState(const std::shared_ptr<Controller>& controller,
                     const std::shared_ptr<WizardStatesFactory>& states_factory,
                     const std::shared_ptr<ConsolePrinter>& printer,
                     const std::shared_ptr<ConsoleReader>& reader) :
                     WizardStateController(controller, states_factory, printer, reader) {

}

std::shared_ptr<WizardStateConsole> ShowState::Execute(std::shared_ptr<WizardContext> context) {
    std::string tasks_show = GetController()->GetAllTasks();
    GetConsolePrinter()->Write(tasks_show);
    return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::NEXT);
}
