//
// Created by Maksym Kharchenko on 25.01.2022.
//

#include "TaskManagerService.grpc.pb.h"

#include "view/commands/factory/CommandFactory.h"
#include "view/states/factory/StatesFactory.h"
#include "view/user_interface/console_io/ConsolePrinter.h"
#include "view/user_interface/console_io/ConsoleReader.h"
#include "view/user_interface/UserInterface.h"
#include "view/ViewController.h"
#include "client/GRPCClientEndPoint.h"
#include "controller/DefaultModelController.h"

#include "logs/LogInit.h"

#include <grpcpp/grpcpp.h>

#include <string>

int main() {
    logs_init(false);

    std::string target_str = "localhost:8586";

    std::shared_ptr<CommandFactory> command_factory = std::make_shared<CommandFactory>();
    std::shared_ptr<ConsolePrinter> printer = std::make_shared<ConsolePrinter>();
    std::shared_ptr<ConsoleReader> reader = std::make_shared<ConsoleReader>();
    std::shared_ptr<StatesFactory> states_factory = std::make_shared<StatesFactory>(command_factory,
                                                                                    printer,
                                                                                    reader);
    std::unique_ptr<UserInterface> user_interface = std::make_unique<UserInterface>(states_factory, printer);
    std::unique_ptr<ModelController> model_controller = std::make_unique<DefaultModelController>(
            std::make_unique<GRPCClientEndPoint>(TaskManagerService::NewStub(grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials()))),
            std::make_unique<TaskValidator>(),
            std::make_unique<persistence::PersistenceFactory>());
    std::unique_ptr<ViewController> view_controller = std::make_unique<ViewController>(
            std::move(model_controller),
            std::move(user_interface));

    view_controller->RunUserInterface();
}