#include <iostream>

#include "TaskManager.h"
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
// TODO_DONE: DeleteTask unnecessary directories - Done 25.11.2021
// TODO_DONE: Change subtasks structure - Done 02.12.2021
// TODO: Move Task::Priority converter out of Task class
// TODO: Make functionality for task deleting
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
// TODO_DONE: Implement complete command - Done 01.12.2021
// TODO_DONE: Implement delete command - Done 02.12.2021
// TODO_DONE: Implement show command - Done 30.11.2021
// TODO_DONE: Implement add_subtask command - Done 02.12.2021
// TODO: Make complete method work with subtasks
// TODO: AddTask WizardStateMachine for states that starts state machine?
// TODO_DONE: Make DueTime validator in controller - Done 01.12.2021
// TODO_DONE: Get rid of exceptions in task manager API - Done 01.12.2021
// TODO_DONE: Make general model interface - Done 01.12.2021
// TODO: Make general controller interface?
// TODO_DONE: Make to_string method for TaskId - Done 02.12.2021
// TODO_DONE: Rework GetIdFromUser method to get invitation string and do controller checks - Done 02.12.2021
// TODO: Make TaskId::Create not throw exception on incorrect string
// TODO_DONE: Delete NullTaskId constant - Done 02.12.2021