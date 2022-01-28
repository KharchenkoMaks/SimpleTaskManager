//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "HelpState.h"

HelpState::HelpState(const StateType next_state,
                     const std::shared_ptr<ConsolePrinter>& printer) :
                     next_state_(next_state),
                     printer_(printer) {}

StateType HelpState::Execute(StateContext& context) {
    printer_->WriteLine("Available commands:");
    printer_->WriteLine("1. add");
    printer_->WriteLine("2. add_subtask");
    printer_->WriteLine("3. edit");
    printer_->WriteLine("4. delete");
    printer_->WriteLine("5. complete");
    printer_->WriteLine("6. add_label");
    printer_->WriteLine("7. remove_label");
    printer_->WriteLine("8. show");
    printer_->WriteLine("9. save");
    printer_->WriteLine("10. load");
    printer_->WriteLine("11. quit");

    return next_state_;
}
