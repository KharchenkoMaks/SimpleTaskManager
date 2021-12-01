#include <iostream>

#include "ConsoleStateMachine.h"
#include "states/factory/WizardStatesFactory.h"
#include "Controller.h"

#include <memory>

int main() {
    std::shared_ptr<Controller> controller =
            std::make_shared<Controller>(std::make_unique<TaskManager>(std::make_unique<IdGenerator>()),
                            std::make_unique<TaskValidator>());
    std::shared_ptr<WizardStatesFactory> states_factory = std::make_shared<WizardStatesFactory>(controller);
    ConsoleStateMachine state_machine(std::make_shared<WizardContext>(), states_factory->GetInitialState());
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
// TODO_DONE: Make Task due time wrapper - Done 30.11.2021
// TODO_DONE: Split MultiFunctionalPrinter to printer and reader - Done 26.11.2021
// TODO_DONE: Make printer and reader private in WizardStateConsole - Done 26.11.2021
// TODO_DONE: Move factory to states' parameters - Done 29.11.2021
// TODO_DONE: Make read id method in WizardStateConsole - Done 29.11.2021
// TODO: Make start_from enum parameter in state machine?
// TODO_DONE: Make controller and validator for tasks - Done 29.11.2021
// TODO_DONE: Inject controller to state machine and states - Done 30.11.2021
// TODO_DONE: Make WizardStatesConsole base class of states? - Done 30.11.2021
// TODO_DONE: Give user choice to keep value of editing task - Done 30.11.2021
// TODO: Implement complete command
// TODO: Implement delete command
// TODO_DONE: Implement show command - Done 30.11.2021
// TODO: Implement add_subtask command
// TODO: Add WizardStateMachine for states that starts state machine?
// TODO_DONE: Make DueTime validator in controller - Done 01.01.2021
// TODO: Get rid of exceptions in task manager API
// TODO: Make general model interface
// TODO: Make general controller interface?