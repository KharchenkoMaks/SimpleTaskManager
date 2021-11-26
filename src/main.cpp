#include <iostream>

#include "ConsoleStateMachine.h"
#include "states/factory/WizardStatesFactory.h"

int main() {
    ConsoleStateMachine state_machine;
    state_machine.Run(WizardStatesFactory::States::kRoot);
    return 0;
}

// TODO (Maksym): Make context inside StateMachine unique
// TODO_DONE: Get rid of unnecessary fields in Context - Done 25.11.2021
// TODO: Move factory, context out of state machine
// TODO_DONE: Get rid of ConfirmState - Done 25.11.2021
// TODO: Move next steps logic to states factory
// TODO: Make lazy states initialization in states factory
// TODO_DONE: Use state machine inside AddTaskState and EditTaskState - Done 25.11.2021
// TODO: Make abstract State for states that run state machine inside?
// TODO: Rename WizardStatePrinter abstract class
// TODO_DONE: Rename Printer to PrinterWithScanner =) - Done 25.11.2021
// TODO: Make default methods in WizardStatePrinter to ask user for some input
// TODO_DONE: Delete unnecessary directories - Done 25.11.2021
// TODO: Change subtasks structure
// TODO: Move Task::Priority converter out of Task class