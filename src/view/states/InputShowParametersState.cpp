//
// Created by Maksym Kharchenko on 30.11.2021.
//

#include "InputShowParametersState.h"
#include "user_interface/console_io/ConsoleUtilities.h"
#include "utilities/TaskConvertors.h"

InputShowParametersState::InputShowParametersState(const StateType next_state,
                                                   const std::shared_ptr<CommandFactory>& command_factory,
                                                   std::unique_ptr<ConsoleStateMachine> state_machine) :
                                                   next_state_(next_state),
                                                   command_factory_(command_factory),
                                                   state_machine_(std::move(state_machine)) {}

StateType InputShowParametersState::Execute(StateContext& context) {
    std::shared_ptr<StateContext> context_with_show_parameters = state_machine_->Run();

    context.SetTaskLabel(context_with_show_parameters->GetTaskLabel());
    context.SetCommand(command_factory_->CreateShowCommand(context));
    return next_state_;
}
