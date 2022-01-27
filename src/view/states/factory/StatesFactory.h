//
// Created by Maksym Kharchenko on 23.11.2021.
//

#ifndef SIMPLETASKMANAGER_STATESFACTORY_H
#define SIMPLETASKMANAGER_STATESFACTORY_H

#include "states/State.h"
#include "user_interface/console_io/ConsolePrinter.h"
#include "user_interface/console_io/ConsoleReader.h"
#include "ModelController.h"
#include "user_interface/ConsoleStateMachine.h"
#include "commands/factory/CommandFactory.h"

#include <memory>
#include <string>
#include <optional>

class StatesFactory {
public:
    StatesFactory(const std::shared_ptr<CommandFactory>& command_factory,
                  const std::shared_ptr<ConsolePrinter>& printer,
                  const std::shared_ptr<ConsoleReader>& reader);

public:
    virtual std::unique_ptr<ConsoleStateMachine> CreateStateMachine(StateType initial_state,
                                                                    const std::shared_ptr<StateContext>& context);

public:
    std::shared_ptr<State> GetState(StateType state);

public:
    virtual ~StatesFactory() = default;

private:
    void InitializeState(StateType state);

private:
    std::map<StateType, std::shared_ptr<State>> states_;

    std::shared_ptr<ConsolePrinter> printer_;
    std::shared_ptr<ConsoleReader> reader_;

    std::shared_ptr<CommandFactory> command_factory_;
};


#endif //SIMPLETASKMANAGER_STATESFACTORY_H
