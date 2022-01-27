//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "HelpState.h"

HelpState::HelpState(const std::shared_ptr<StatesFactory>& factory) :
                    factory_(factory) {

}

std::shared_ptr<State> HelpState::Execute(StateContext& context) {
    factory_.lock()->GetConsolePrinter()->WriteLine("Available commands:");
    factory_.lock()->GetConsolePrinter()->WriteLine("1. add");
    factory_.lock()->GetConsolePrinter()->WriteLine("2. add_subtask");
    factory_.lock()->GetConsolePrinter()->WriteLine("3. edit");
    factory_.lock()->GetConsolePrinter()->WriteLine("4. delete");
    factory_.lock()->GetConsolePrinter()->WriteLine("5. complete");
    factory_.lock()->GetConsolePrinter()->WriteLine("6. add_label");
    factory_.lock()->GetConsolePrinter()->WriteLine("7. remove_label");
    factory_.lock()->GetConsolePrinter()->WriteLine("8. show");
    factory_.lock()->GetConsolePrinter()->WriteLine("9. save");
    factory_.lock()->GetConsolePrinter()->WriteLine("10. load");
    factory_.lock()->GetConsolePrinter()->WriteLine("11. quit");

    return factory_.lock()->GetNextState(*this, StatesFactory::MoveType::NEXT);
}
