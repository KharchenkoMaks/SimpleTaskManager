//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "HelpState.h"

HelpState::HelpState(std::unique_ptr<StateDependencies> dependencies) :
                    dependencies_(std::move(dependencies)) {

}

std::shared_ptr<WizardStateInterface> HelpState::Execute(std::shared_ptr<WizardContext> context) {
    dependencies_->GetConsolePrinter()->WriteLine("Available commands:");
    dependencies_->GetConsolePrinter()->WriteLine("1. add");
    dependencies_->GetConsolePrinter()->WriteLine("2. add_subtask");
    dependencies_->GetConsolePrinter()->WriteLine("3. edit");
    dependencies_->GetConsolePrinter()->WriteLine("4. delete");
    dependencies_->GetConsolePrinter()->WriteLine("5. complete");
    dependencies_->GetConsolePrinter()->WriteLine("6. label");
    dependencies_->GetConsolePrinter()->WriteLine("7. show");
    dependencies_->GetConsolePrinter()->WriteLine("8. save");
    dependencies_->GetConsolePrinter()->WriteLine("9. load");
    dependencies_->GetConsolePrinter()->WriteLine("10. quit");

    return dependencies_->GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::NEXT);
}
