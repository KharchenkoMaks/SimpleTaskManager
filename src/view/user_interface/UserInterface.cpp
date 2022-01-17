//
// Created by Maksym Kharchenko on 23.12.2021.
//

#include "UserInterface.h"
#include "utilities/TaskConvertors.h"

UserInterface::UserInterface(const std::shared_ptr<StatesFactory>& states_factory) :
                             states_factory_(states_factory) {

}

std::shared_ptr<Command> UserInterface::AskUserForAction() {
    auto state_machine = states_factory_->CreateStateMachine(states_factory_->GetRootState(),
                                                             std::make_shared<StateContext>());
    std::shared_ptr<StateContext> result_context = state_machine->Run();

    return result_context->GetCommand();
}

void UserInterface::PrintAddedTaskId(const TaskId& task_id) {
    states_factory_->GetConsolePrinter()->WriteLine("Task was successfully added, TaskId: " + std::to_string(task_id.id()));
}

void UserInterface::PrintRequestResult(ControllerRequestResult action_result) {
    switch (action_result) {
        case ControllerRequestResult::SUCCESS:
            states_factory_->GetConsolePrinter()->WriteLine("Action success.");
            break;
        case ControllerRequestResult::FAIL_INVALID_TASK:
            states_factory_->GetConsolePrinter()->WriteError("Invalid task was given.");
            break;
        case ControllerRequestResult::FAIL_UNCOMPLETED_SUBTASKS:
            states_factory_->GetConsolePrinter()->WriteError("Found uncompleted subtasks of this task.");
            break;
        case ControllerRequestResult::FAIL_NOT_DELETED_SUBTASKS:
            states_factory_->GetConsolePrinter()->WriteError("Found not deleted subtask of this task.");
            break;
        case ControllerRequestResult::FAIL_NO_SUCH_TASK:
            states_factory_->GetConsolePrinter()->WriteError("No task with such id was found.");
            break;
        case ControllerRequestResult::FILE_WAS_NOT_OPENED:
            states_factory_->GetConsolePrinter()->WriteError("Couldn't open the file.");
            break;
        case ControllerRequestResult::FILE_DAMAGED:
            states_factory_->GetConsolePrinter()->WriteError("File is damaged.");
            break;
        case ControllerRequestResult::FAIL_LABEL_ALREADY_SET:
            states_factory_->GetConsolePrinter()->WriteError("This label is already set to current task.");
            break;
        case ControllerRequestResult::FAIL_NO_SUCH_LABEL:
            states_factory_->GetConsolePrinter()->WriteError("Fail to remove label, current task doesn't include such label.");
            break;
    }
}

void UserInterface::ShowTasks(const std::vector<RelationalTask>& tasks) {
    std::shared_ptr<StateContext> context = std::make_shared<StateContext>();
    context->SetTasksToShow(tasks);

    auto state_machine = states_factory_->CreateStateMachine(states_factory_->GetShowState(), context);

    state_machine->Run();
}
