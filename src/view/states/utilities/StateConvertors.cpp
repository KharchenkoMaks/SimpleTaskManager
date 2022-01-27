//
// Created by Maksym Kharchenko on 27.01.2022.
//

#include "StateConvertors.h"

std::optional<StateType> GetStateByUserCommand(const std::string& command) {
    if (command == "add") {
        return StateType::kAddTask;
    } else if (command == "add_subtask") {
        return (StateType::kAddSubTask);
    } else if (command == "edit") {
        return (StateType::kEditTask);
    } else if (command == "delete") {
        return (StateType::kDelete);
    } else if (command == "complete") {
        return (StateType::kComplete);
    } else if (command == "show") {
        return (StateType::kInputShowParameters);
    } else if (command == "help") {
        return (StateType::kHelp);
    } else if (command == "quit") {
        return (StateType::kQuit);
    } else if (command == "label") {
        return (StateType::kSetLabel);
    } else if (command == "save") {
        return (StateType::kSave);
    } else if (command == "load") {
        return (StateType::kLoad);
    } else {
        return std::nullopt;
    }
}
