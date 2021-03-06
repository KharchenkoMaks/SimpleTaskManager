//
// Created by Maksym Kharchenko on 21.12.2021.
//

#ifndef SIMPLETASKMANAGER_EDITTASKCOMMAND_H
#define SIMPLETASKMANAGER_EDITTASKCOMMAND_H

#include "Command.h"
#include "Task.pb.h"
#include "controller/ModelController.h"
#include "utilities/TaskBuilder.h"
#include "controller/ControllerRequestResult.h"

#include <memory>

class EditTaskCommand : public Command {
public:
    EditTaskCommand(const TaskBuilder& task_builder,
                    const TaskId& task_id);
public:
    CommandResult Execute(const std::shared_ptr<ModelController>& controller) override;
private:
    TaskBuilder task_builder_;
    TaskId task_id_;
};


#endif //SIMPLETASKMANAGER_EDITTASKCOMMAND_H
