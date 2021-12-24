//
// Created by Maksym Kharchenko on 21.12.2021.
//

#include "EditTaskCommand.h"

EditTaskCommand::EditTaskCommand(const TaskBuilder& task_builder,
                                 const TaskId& task_id) :
                                 task_builder_(task_builder),
                                 task_id_(task_id) {

}

CommandResult EditTaskCommand::Execute(const std::shared_ptr<Controller>& controller) {
    auto editing_task = controller->GetTask(task_id_);
    if (!editing_task.has_value()) {
        return CommandResult::Create(ControllerRequestResult::FAIL_NO_SUCH_TASK);
    }
    Task edited_task = task_builder_.Merge(editing_task.value().task()).BuildTask();

    return CommandResult::Create(controller->EditTask(task_id_, edited_task));
}
