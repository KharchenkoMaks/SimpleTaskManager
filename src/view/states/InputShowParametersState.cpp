//
// Created by Maksym Kharchenko on 30.11.2021.
//

#include "InputShowParametersState.h"
#include "user_interface/console_io/ConsoleUtilities.h"
#include "utilities/TaskConvertors.h"

InputShowParametersState::InputShowParametersState(const std::shared_ptr<StatesFactory>& factory) :
                    factory_(factory) {

}

std::shared_ptr<State> InputShowParametersState::Execute(StateContext& context) {
    auto state_machine = factory_.lock()->CreateStateMachine(factory_.lock()->GetInputShowParametersInitialState(),
                                                             std::make_shared<StateContext>());

    std::shared_ptr<StateContext> context_with_show_parameters = state_machine->Run();

    context.SetTaskLabel(context_with_show_parameters->GetTaskLabel());
    context.SetCommand(factory_.lock()->GetCommandFactory()->CreateShowCommand(context));
    return factory_.lock()->GetNextState(*this, StatesFactory::MoveType::NEXT);
}
