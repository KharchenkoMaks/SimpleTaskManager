//
// Created by Maksym Kharchenko on 23.11.2021.
//

#ifndef SIMPLETASKMANAGER_STATEINTERFACE_H
#define SIMPLETASKMANAGER_STATEINTERFACE_H

#include "StateContext.h"
#include "console_io/ConsolePrinter.h"
#include "console_io/ConsoleReader.h"

#include <memory>
#include <optional>

class StateInterface {
public:
    virtual std::shared_ptr<StateInterface> Execute(std::shared_ptr<StateContext>) = 0;

public:
    virtual ~StateInterface() = default;
};


#endif //SIMPLETASKMANAGER_STATEINTERFACE_H
