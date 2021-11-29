#include <iostream>

#include "ConsoleStateMachine.h"
#include "states/factory/WizardStatesFactory.h"

#include <memory>

int main() {
    std::shared_ptr<WizardStatesFactory> states_factory = std::make_shared<WizardStatesFactory>();
    ConsoleStateMachine state_machine(states_factory->GetInitialState());
    state_machine.Run();
    return 0;
}

// TODO (Maksym): Make context inside StateMachine unique?
// TODO_DONE: Get rid of unnecessary fields in Context - Done 25.11.2021
// TODO_DONE: Move factory, context out of state machine - Done 26.11.2021
// TODO_DONE: Get rid of ConfirmState - Done 25.11.2021
// TODO_DONE: Move next steps logic to states factory - Done 26.11.2021
// TODO_DONE: Make lazy states initialization in states factory - Done 29.11.2021
// TODO_DONE: Get rid of states enum in states factory - Done 26.11.2021
// TODO_DONE: Use state machine inside AddTaskState and EditTaskState - Done 25.11.2021
// TODO: Make abstract State for states that run state machine inside?
// TODO_DONE: Rename WizardStateConsole abstract class - Done 26.11.2021
// TODO_DONE: Rename Printer to PrinterWithScanner =) - Done 25.11.2021
// TODO_DONE: Make default methods in WizardStateConsole to ask user for some input - Done 26.11.2021
// TODO_DONE: Delete unnecessary directories - Done 25.11.2021
// TODO: Change subtasks structure
// TODO: Move Task::Priority converter out of Task class
// TODO_DONE: Split MultiFunctionalPrinter to printer and reader - Done 26.11.2021
// TODO_DONE: Make printer and reader private in WizardStateConsole - Done 26.11.2021
// TODO_DONE: Move factory to states' parameters - Done 29.11.2021
// TODO_DONE: Make read id method in WizardStateConsole - Done 29.11.2021
// TODO: Make start_from enum parameter in state machine?