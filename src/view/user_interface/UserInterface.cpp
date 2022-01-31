//
// Created by Maksym Kharchenko on 23.12.2021.
//

#include "UserInterface.h"
#include "utilities/TaskConvertors.h"

UserInterface::UserInterface(const std::shared_ptr<StatesFactory>& states_factory,
                             const std::shared_ptr<ConsolePrinter>& printer) :
                             states_factory_(states_factory),
                             printer_(printer) {}

std::shared_ptr<Command> UserInterface::AskUserForAction() {
    auto state_machine = states_factory_->CreateStateMachine(states_factory_->GetRootState(),
                                                             std::make_shared<StateContext>());
    std::shared_ptr<StateContext> result_context = state_machine->Run();

    return result_context->GetCommand();
}

void UserInterface::PrintAddedTaskId(const TaskId& task_id) {
    printer_->WriteLine("Task was successfully added, TaskId: " + std::to_string(task_id.id()));
}

void UserInterface::PrintRequestResult(ControllerRequestResult action_result) {
    switch (action_result) {
        case ControllerRequestResult::SUCCESS:
            printer_->WriteLine("Action success.");
            break;
        case ControllerRequestResult::FAIL_INVALID_TASK:
            printer_->WriteError("Invalid task was given.");
            break;
        case ControllerRequestResult::FAIL_UNCOMPLETED_SUBTASKS:
            printer_->WriteError("Found uncompleted subtasks of this task.");
            break;
        case ControllerRequestResult::FAIL_NOT_DELETED_SUBTASKS:
            printer_->WriteError("Found not deleted subtask of this task.");
            break;
        case ControllerRequestResult::FAIL_NO_SUCH_TASK:
            printer_->WriteError("No task with such id was found.");
            break;
        case ControllerRequestResult::FILE_WAS_NOT_OPENED:
            printer_->WriteError("Couldn't open the file.");
            break;
        case ControllerRequestResult::FILE_DAMAGED:
            printer_->WriteError("File is damaged.");
            break;
        case ControllerRequestResult::FAIL_NO_SUCH_LABEL:
            printer_->WriteError("Fail to remove label, current task doesn't include such label.");
            break;
        case ControllerRequestResult::FAIL_SERVER_TROUBLES:
            states_factory_->GetConsolePrinter()->WriteError("Fail, server troubles.");
            break;
    }
}

void UserInterface::ShowTasks(const std::vector<RelationalTask>& tasks) {
    std::shared_ptr<StateContext> context = std::make_shared<StateContext>();
    context->SetTasksToShow(tasks);

    auto state_machine = states_factory_->CreateStateMachine(states_factory_->GetShowState(), context);

    state_machine->Run();
}
