//
// Created by Maksym Kharchenko on 21.12.2021.
//

#include "AddTaskCommand.h"

AddTaskCommand::AddTaskCommand(const std::shared_ptr<Controller>& controller, const Task& task) :
                                controller_(controller),
                                task_(task) {

}
