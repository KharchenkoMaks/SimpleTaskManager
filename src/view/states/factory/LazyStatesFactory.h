//
// Created by Maksym Kharchenko on 31.01.2022.
//

#ifndef SIMPLETASKMANAGER_LAZYSTATESFACTORY_H
#define SIMPLETASKMANAGER_LAZYSTATESFACTORY_H

#include "StatesFactory.h"

#include "user_interface/console_io/ConsolePrinter.h"
#include "user_interface/console_io/ConsoleReader.h"
#include "commands/factory/CommandFactory.h"

class LazyStatesFactory : public StatesFactory {
public:
    LazyStatesFactory(const std::shared_ptr<CommandFactory>& command_factory,
                      const std::shared_ptr<ConsolePrinter>& printer,
                      const std::shared_ptr<ConsoleReader>& reader);
public:
    std::shared_ptr<State> GetState(StateType state) override;
    std::unique_ptr<ConsoleStateMachine> CreateStateMachine(StateType initial_state,
                                                            std::unique_ptr<StateContext> context,
                                                            const std::shared_ptr<StatesFactory>& states_factory) override;

private:
    std::unique_ptr<ConsoleStateMachine> CreateStateMachine(StateType initial_state, std::unique_ptr<StateContext> context);
    void InitializeState(StateType state);

private:
    std::map<StateType, std::shared_ptr<State>> states_;

    std::shared_ptr<ConsolePrinter> printer_;
    std::shared_ptr<ConsoleReader> reader_;

    std::shared_ptr<CommandFactory> command_factory_;
};

#endif //SIMPLETASKMANAGER_LAZYSTATESFACTORY_H
