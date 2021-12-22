//
// Created by Maksym Kharchenko on 21.12.2021.
//

#include "SetLabelCommand.h"

SetLabelCommand::SetLabelCommand(const TaskId& task_id,
                                 const std::string& label) :
                                 task_id_(task_id),
                                 label_(label) {

}
