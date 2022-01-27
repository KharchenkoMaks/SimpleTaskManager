//
// Created by Maksym Kharchenko on 27.01.2022.
//

#ifndef SIMPLETASKMANAGER_STATECONVERTORS_H
#define SIMPLETASKMANAGER_STATECONVERTORS_H

#include "states/State.h"

#include <optional>

std::optional<StateType> GetStateByUserCommand(const std::string& command);


#endif //SIMPLETASKMANAGER_STATECONVERTORS_H
