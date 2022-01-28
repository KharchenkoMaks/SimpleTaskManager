//
// Created by Maksym Kharchenko on 23.11.2021.
//

#ifndef SIMPLETASKMANAGER_STATE_H
#define SIMPLETASKMANAGER_STATE_H

#include "user_interface/StateContext.h"

#include <memory>
#include <optional>

enum class StateType;

class State {
public:
    virtual StateType Execute(StateContext&) = 0;

public:
    virtual ~State() = default;
};

enum class StateType {
    kRoot,
    kHelp,
    kQuit,
    kAddTask,
    kAddSubTask,
    kEditTask,
    kInputTaskTitle,
    kInputTaskPriority,
    kInputTaskDueDate,
    kInputShowParameters,
    kComplete,
    kDelete,
    kSetLabel,
    kEnd,
    kSave,
    kLoad,
    kShow,
    kRemoveLabel
};


#endif //SIMPLETASKMANAGER_STATE_H
