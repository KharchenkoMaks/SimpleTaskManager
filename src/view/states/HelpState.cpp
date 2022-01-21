//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "HelpState.h"

HelpState::HelpState(const std::shared_ptr<StatesFactory>& factory) :
                    factory_(factory) {

}

std::shared_ptr<State> HelpState::Execute(StateContext& context) {
    factory_->GetConsolePrinter()->WriteLine("Available commands:");
    factory_->GetConsolePrinter()->WriteLine("1. add");
    factory_->GetConsolePrinter()->WriteLine("2. add_subtask");
    factory_->GetConsolePrinter()->WriteLine("3. edit");
    factory_->GetConsolePrinter()->WriteLine("4. delete");
    factory_->GetConsolePrinter()->WriteLine("5. complete");
    factory_->GetConsolePrinter()->WriteLine("6. label");
    factory_->GetConsolePrinter()->WriteLine("7. show");
    factory_->GetConsolePrinter()->WriteLine("8. save");
    factory_->GetConsolePrinter()->WriteLine("9. load");
    factory_->GetConsolePrinter()->WriteLine("10. quit");

    return factory_->GetNextState(*this, StatesFactory::MoveType::NEXT);
}
