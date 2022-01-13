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

        CommandResult cmd_result = user_command->Execute(controller_);

        if (cmd_result.GetResult() == ControllerRequestResult::SUCCESS) {
            if (cmd_result.GetTaskId() != std::nullopt) {
                user_interface_->PrintAddedTaskId(cmd_result.GetTaskId().value());
            } else if (!cmd_result.GetTasksToShow().empty()) {
                user_interface_->ShowTasks(cmd_result.GetTasksToShow());
            }
        }

        user_interface_->PrintRequestResult(cmd_result.GetResult());
    }
}
