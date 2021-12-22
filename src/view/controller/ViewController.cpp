//
// Created by Maksym Kharchenko on 21.12.2021.
//

#include "ViewController.h"

ViewController::ViewController(std::unique_ptr<ConsoleStateMachine> state_machine,
                               std::unique_ptr<StatesFactory> states_factory,
                               std::unique_ptr<Controller> controller) :
                               state_machine_(std::move(state_machine)),
                               states_factory_(std::move(states_factory)),
                               controller_(std::move(controller)) {

}

void ViewController::RunUserInterface() {
    while (true) {
        std::shared_ptr<StateContext> state_context =
                state_machine_->Run(std::make_shared<StateContext>(), states_factory_->GetInitialState());
        if (state_context->GetCommand() == nullptr)
            break;
        state_context->GetCommand()->Execute();
    }
}
