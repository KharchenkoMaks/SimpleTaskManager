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

void UserInterface::PrintResult(TaskActionResult action_result) {
    switch (action_result) {
        case TaskActionResult::SUCCESS: {
            states_factory_->GetPrinter()->WriteLine("Action success.");
            break;
        }
        case TaskActionResult::FAIL_INVALID_TASK: {
            states_factory_->GetPrinter()->WriteError("Invalid task was given.");
            break;
        }
        case TaskActionResult::FAIL_CONTROVERSIAL_SUBTASKS: {
            states_factory_->GetPrinter()->WriteError("Found unresolved subtasks.");
            break;
        }
        case TaskActionResult::FAIL_NO_SUCH_TASK: {
            states_factory_->GetPrinter()->WriteError("No task with such id was found.");
            break;
        }
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
