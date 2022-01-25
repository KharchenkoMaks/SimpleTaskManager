//
// Created by Maksym Kharchenko on 25.01.2022.
//

#include "ModelControllerService.grpc.pb.h"

#include "view/commands/factory/CommandFactory.h"
#include "view/states/factory/StatesFactory.h"
#include "view/user_interface/console_io/ConsolePrinter.h"
#include "view/user_interface/console_io/ConsoleReader.h"
#include "view/user_interface/UserInterface.h"
#include "view/ViewController.h"
#include "view/GRPCModelController.h"

#include <grpcpp/grpcpp.h>

#include <string>

int main() {
    std::string target_str = "localhost:8586";

    std::shared_ptr<CommandFactory> command_factory = std::make_shared<CommandFactory>();
    std::shared_ptr<StatesFactory> states_factory = std::make_shared<StatesFactory>(command_factory,
                                                                                    std::make_unique<ConsolePrinter>(),
                                                                                    std::make_unique<ConsoleReader>());
    std::unique_ptr<UserInterface> user_interface = std::make_unique<UserInterface>(
            states_factory);
    std::unique_ptr<ModelController> model_controller =
            std::make_unique<GRPCModelController>(ModelControllerService::NewStub(grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials())));
    std::unique_ptr<ViewController> view_controller = std::make_unique<ViewController>(
            std::move(model_controller),
            std::move(user_interface));

    view_controller->RunUserInterface();
}