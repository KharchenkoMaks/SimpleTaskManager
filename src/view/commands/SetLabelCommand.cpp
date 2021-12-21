//
// Created by Maksym Kharchenko on 21.12.2021.
//

#include "SetLabelCommand.h"

SetLabelCommand::SetLabelCommand(const std::shared_ptr<Controller>& controller,
                                 const std::shared_ptr<ConsolePrinter>& printer,
                                 const TaskId& task_id,
                                 const std::string& label) :
                                 controller_(controller),
                                 printer_(printer),
                                 task_id_(task_id),
                                 label_(label) {

}
