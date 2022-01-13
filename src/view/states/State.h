//
// Created by Maksym Kharchenko on 23.11.2021.
//

#ifndef SIMPLETASKMANAGER_STATE_H
#define SIMPLETASKMANAGER_STATE_H

#include "user_interface/StateContext.h"
#include "user_interface/console_io/ConsolePrinter.h"
#include "user_interface/console_io/ConsoleReader.h"

#include <memory>
#include <optional>

class State {
public:
    virtual std::shared_ptr<State> Execute(StateContext&) = 0;

public:
    virtual ~State() = default;
};


#endif //SIMPLETASKMANAGER_STATE_H
