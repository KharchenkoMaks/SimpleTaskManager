#include <iostream>

#include "ConsoleStateMachine.h"
#include "states/factory/WizardStatesFactory.h"

int main() {
    ConsoleStateMachine state_machine;
    state_machine.Run(WizardStatesFactory::States::kRoot);
    return 0;
}

// TODO (Maksym): Make context inside StateMachine unique
// TODO: Move factory, context out of state machine
// TODO: Get rid of ConfirmState
// TODO: Move next steps logic to states factory
// TODO: Make lazy states initialization in states factory
// TODO: Use state machine inside AddTaskState and EditTaskState
// TODO: Make abstract State for states that run state machine inside?
// TODO: Rename WizardStatePrinter abstract class
// TODO: Rename Printer to PrinterWithScanner =)
// TODO: Make default methods in WizardStatePrinter to ask user for some input
// TODO: Delete unnecessary directories
// TODO: Change subtasks structure