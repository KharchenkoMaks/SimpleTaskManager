//
// Created by Maksym Kharchenko on 23.12.2021.
//

#include "UserInterface.h"
#include "utilities/TaskConvertors.h"

UserInterface::UserInterface(const std::shared_ptr<StatesFactory>& states_factory) :
                             states_factory_(states_factory) {

}

std::shared_ptr<CommandInterface> UserInterface::AskUserForAction() {
    auto state_machine = states_factory_->CreateStateMachine();
    std::shared_ptr<StateContext> result_context =
            state_machine->Run(std::make_shared<StateContext>(), states_factory_->GetInitialState());

    return result_context->GetCommand();
}

void UserInterface::PrintAddedTaskId(const TaskId& task_id) {
    states_factory_->GetPrinter()->WriteLine("Task was successfully added, TaskId: " + std::to_string(task_id.id()));
}

void UserInterface::PrintResult(ControllerRequestResult action_result) {
    switch (action_result) {
        case ControllerRequestResult::SUCCESS: {
            states_factory_->GetPrinter()->WriteLine("Action success.");
            break;
        }
        case ControllerRequestResult::FAIL_INVALID_TASK: {
            states_factory_->GetPrinter()->WriteError("Invalid task was given.");
            break;
        }
        case ControllerRequestResult::FAIL_UNCOMPLETED_SUBTASKS: {
            states_factory_->GetPrinter()->WriteError("Found uncompleted subtasks of this task.");
            break;
        }
        case ControllerRequestResult::FAIL_NOT_DELETED_SUBTASKS: {
            states_factory_->GetPrinter()->WriteError("Found not deleted subtask of this task.");
            break;
        }
        case ControllerRequestResult::FAIL_NO_SUCH_TASK: {
            states_factory_->GetPrinter()->WriteError("No task with such id was found.");
            break;
        }
        case ControllerRequestResult::FILE_WAS_NOT_OPENED:
            states_factory_->GetPrinter()->WriteError("Couldn't open the file.");
            break;
        case ControllerRequestResult::FILE_DAMAGED:
            states_factory_->GetPrinter()->WriteError("File is damaged.");
            break;
    }
}

void UserInterface::ShowTasks(const std::vector<TaskTransfer>& tasks) {
    for (auto task : tasks) {
        std::string task_string;
        if (task.has_parent_id()) {
            task_string += "\t";
        }
        task_string += TaskToString(task.task_id(), task.task());
        states_factory_->GetPrinter()->WriteLine(task_string);
    }
}
