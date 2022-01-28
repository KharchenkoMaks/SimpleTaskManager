//
// Created by Maksym Kharchenko on 30.11.2021.
//

#include "InputShowParametersState.h"
#include "user_interface/console_io/ConsoleUtilities.h"
#include "utilities/TaskConvertors.h"

InputShowParametersState::InputShowParametersState(const StateType next_state,
                                                   const std::shared_ptr<CommandFactory>& command_factory) :
                                                   next_state_(next_state),
                                                   command_factory_(command_factory) {}

StateType InputShowParametersState::Execute(StateContext& context) {
    context.SetCommand(command_factory_->CreateShowCommand(context));
    return next_state_;
}
