//
// Created by Maksym Kharchenko on 21.12.2021.
//

#ifndef SIMPLETASKMANAGER_EDITTASKCOMMAND_H
#define SIMPLETASKMANAGER_EDITTASKCOMMAND_H

#include "CommandInterface.h"
#include "Task.pb.h"
#include "controller/Controller.h"
#include "console_io/ConsolePrinter.h"
#include "utilities/TaskBuilder.h"

#include <memory>

class EditTaskCommand : public CommandInterface {
public:
    EditTaskCommand(const std::shared_ptr<Controller>& controller,
                    const std::shared_ptr<ConsolePrinter>& printer,
                    const TaskBuilder& task_builder,
                    const TaskId& task_id);
public:
    void Execute() override;
private:
    TaskBuilder task_builder_;
    TaskId task_id_;

    std::shared_ptr<ConsolePrinter> printer_;

    std::shared_ptr<Controller> controller_;
};


#endif //SIMPLETASKMANAGER_EDITTASKCOMMAND_H
