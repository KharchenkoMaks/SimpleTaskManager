#include "TaskManager.h"
#include "model/SequentIdGenerator.h"
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
            std::make_unique<TaskManager>(std::make_unique<SequentIdGenerator>()),
            std::make_unique<TaskValidator>(),
            std::make_unique<persistence::PersistenceFactory>());
    auto view_controller = std::make_unique<ViewController>(std::move(model_controller), std::move(user_interface));

    view_controller->RunUserInterface();
    return 0;
}
