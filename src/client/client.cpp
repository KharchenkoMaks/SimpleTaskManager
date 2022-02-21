//
// Created by Maksym Kharchenko on 25.01.2022.
//

#include "TaskManagerService.grpc.pb.h"

#include "view/commands/factory/CommandFactory.h"
#include "view/states/factory/LazyStatesFactory.h"
#include "view/user_interface/console_io/ConsolePrinter.h"
#include "view/user_interface/console_io/ConsoleReader.h"
#include "view/user_interface/UserInterface.h"
#include "view/ViewController.h"
#include "client/GRPCClientEndPoint.h"
#include "controller/DefaultModelController.h"

#include "options/ProgramOptionsParsers.h"

#include "logs/DefaultLogging.h"

#include <grpcpp/grpcpp.h>

#include <string>

int main(int argc, char* argv[]) {
    std::string target_str = parse_options_host(argc, argv, "localhost", "8586");

    LOG_TRIVIAL(info) << "Client starting with target ip: " << target_str;

    auto command_factory = std::make_shared<CommandFactory>();
    auto printer = std::make_shared<ConsolePrinter>();
    auto reader = std::make_shared<ConsoleReader>();
    auto states_factory = std::make_shared<LazyStatesFactory>(command_factory, printer, reader);
    auto user_interface = std::make_unique<UserInterface>(states_factory, printer);
    auto model_controller = std::make_unique<DefaultModelController>(
            std::make_unique<GRPCClientEndPoint>(TaskManagerService::NewStub(grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials()))),
            std::make_unique<TaskValidator>(),
            std::make_unique<persistence::PersistenceFactory>());
    auto view_controller = std::make_unique<ViewController>(std::move(model_controller), std::move(user_interface));

    view_controller->RunUserInterface();
}