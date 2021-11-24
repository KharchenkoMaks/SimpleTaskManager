#include <iostream>

#include "ConsoleStateMachine.h"
#include "states/factory/WizardStatesFactory.h"

int main() {
    ConsoleStateMachine state_machine;
    state_machine.Run(WizardStatesFactory::States::kRoot);
    return 0;
}
