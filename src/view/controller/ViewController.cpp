//
// Created by Maksym Kharchenko on 21.12.2021.
//

#include "ViewController.h"

ViewController::ViewController(std::unique_ptr<Controller> controller,
                               std::unique_ptr<UserInterface> user_interface) :
                               controller_(std::move(controller)),
                               user_interface_(std::move(user_interface)) {

}

void ViewController::RunUserInterface() {
    while (true) {
        std::shared_ptr<CommandInterface> user_command = user_interface_->AskUserForAction();
        if (user_command == nullptr)
            break;
        
        user_command->Execute(controller_);
    }
}
