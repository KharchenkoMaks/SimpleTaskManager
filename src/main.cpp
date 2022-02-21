#include "TaskManager.h"
#include "states/factory/LazyStatesFactory.h"
#include "DefaultModelController.h"
#include "user_interface/UserInterface.h"
#include "ViewController.h"
#include "persistence/PersistenceFactory.h"

#include "logs/LogInit.h"

#include <memory>

int main() {
    logs_init(boost::log::trivial::severity_level::info, false);

    auto command_factory = std::make_shared<CommandFactory>();
    auto printer = std::make_shared<ConsolePrinter>();
    auto reader = std::make_shared<ConsoleReader>();
    auto states_factory = std::make_shared<LazyStatesFactory>(command_factory, printer, reader);
    auto user_interface = std::make_unique<UserInterface>(states_factory, printer);
    auto model_controller = std::make_unique<DefaultModelController>(
            std::make_unique<TaskManager>(std::make_unique<IdGenerator>()),
            std::make_unique<TaskValidator>(),
            std::make_unique<persistence::PersistenceFactory>());
    auto view_controller = std::make_unique<ViewController>(std::move(model_controller), std::move(user_interface));

    view_controller->RunUserInterface();
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
// TODO_DONE: Make abstract State for states that run state machine inside? - Done 07.12.2021
// TODO_DONE: Rename StateInterface abstract class - Done 26.11.2021
// TODO_DONE: Rename Printer to PrinterWithScanner =) - Done 25.11.2021
// TODO_DONE: Make default methods in StateInterface to ask user for some input - Done 26.11.2021
// TODO_DONE: DeleteTask unnecessary directories - Done 25.11.2021
// TODO_DONE: Change subtasks structure - Done 02.12.2021
// TODO: Move Task::Priority converter out of Task class
// TODO_DONE: Make functionality for task deleting - Done 03.12.2021
// TODO_DONE: Make Task due time wrapper - Done 30.11.2021
// TODO_DONE: Split MultiFunctionalPrinter to printer and reader - Done 26.11.2021
// TODO_DONE: Make printer and reader private in StateInterface - Done 26.11.2021
// TODO_DONE: Move factory to states' parameters - Done 29.11.2021
// TODO_DONE: Make read id method in StateInterface - Done 29.11.2021
// TODO: Make start_from enum parameter in state machine?
// TODO_DONE: Make controller and validator for tasks - Done 29.11.2021
// TODO_DONE: Inject controller to state machine and states - Done 30.11.2021
// TODO_DONE: Make WizardStatesConsole base class of states? - Done 30.11.2021
// TODO_DONE: Give user choice to keep value of editing task - Done 30.11.2021
// TODO_DONE: Implement complete command - Done 01.12.2021
// TODO_DONE: Implement delete command - Done 02.12.2021
// TODO_DONE: Implement show command - Done 30.11.2021
// TODO_DONE: Implement add_subtask command - Done 02.12.2021
// TODO_DONE: Make complete method work with subtasks - Done 06.12.2021
// TODO_DONE: Make delete method work with subtasks - Done 06.12.2021
// TODO_DONE: Make DueTime validator in controller - Done 01.12.2021
// TODO_DONE: Get rid of exceptions in task manager API - Done 01.12.2021
// TODO_DONE: Make general model interface - Done 01.12.2021
// TODO: Make general controller interface?
// TODO_DONE: Make to_string method for TaskId - Done 02.12.2021
// TODO_DONE: Rework GetIdFromUser method to get invitation string and do controller checks - Done 02.12.2021
// TODO_DONE: Make TaskId::Create not throw exception on incorrect string - Done 03.12.2021
// TODO_DONE: Delete NullTaskId constant - Done 02.12.2021
// TODO_DONE: Make label command - Done 06.12.2021
// TODO_DONE: Inject ConsoleMachine in States in factory - Done 07.12.2021
// TODO: Move next states logic to separate class
// TODO: Make state for getting task id from user?
// TODO_DONE: Remove check for task existence in states - Done 08.12.2021
// TODO_DONE: Make user message when non-existent task id was given - Done 09.12.2021
// TODO: Make task validator general, move it to utilities
// TODO_DONE: Make pure State interface - Done 10.12.2021
// TODO_DONE: Return TaskActionResult in Model API - Done 09.12.2021
// TODO: Rename Model
// TODO_DONE: Make TaskBuilder in StateContext - Done 10.12.2021
// TODO: Make set_label part of edit
// TODO: Make builder of integration tests
// TODO_DONE: Make state for ending state machine - Done 09.12.2021
// TODO: Rework states unit tests to test StateDependencies calls
// TODO: Remove states includes in factory header file
// TODO: Remove controller from states
// TODO: Create state machine in factory
// TODO: Remove StateDependencies (free methods, leave only factory)
// TODO: Remove code repeating in task manager tasks container