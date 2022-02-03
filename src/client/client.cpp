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
#include <boost/log/trivial.hpp>
#include <boost/program_options.hpp>

#include <grpcpp/grpcpp.h>

#include <string>
#include <iostream>

void parse_options(int argc, char* argv[]) {
    bool show_logs_in_console = false;
    bool severity_debug = false;

    boost::program_options::options_description desc("Allowed options");

    desc.add_options()
            ("help", "prints help message")
            ("log_console", boost::program_options::bool_switch(&show_logs_in_console), "show logs in console")
            ("debug", boost::program_options::bool_switch(&severity_debug), "enable debug logs");

    boost::program_options::variables_map vm;
    boost::program_options::store(parse_command_line(argc, argv, desc), vm);
    boost::program_options::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << "\n";
        return;
    }

    if (severity_debug)
        logs_init(boost::log::trivial::severity_level::debug, show_logs_in_console);
    else
        logs_init(boost::log::trivial::severity_level::info, show_logs_in_console);
}

int main(int argc, char* argv[]) {
    parse_options(argc, argv);

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