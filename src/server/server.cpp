//
// Created by Maksym Kharchenko on 25.01.2022.
//

#include "server/GRPCServerEndPoint.h"

#include "model/TaskManager.h"
#include "model/IdGenerator.h"

#include "logs/LogInit.h"
#include "logs/DefaultLogging.h"
#include <boost/program_options.hpp>

#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#include <iostream>

std::string parse_options(int argc, char* argv[]) {
    bool severity_debug = false;
    std::string host = "0.0.0.0";
    std::string port = "8586";

    boost::program_options::options_description desc("Allowed options");

    desc.add_options()
            ("help", "prints help message")
            ("debug", boost::program_options::bool_switch(&severity_debug), "enable debug logs")
            ("host", boost::program_options::value(&host), "server host, default: 0.0.0.0")
            ("port", boost::program_options::value(&port), "server port, default: 8586");

    boost::program_options::variables_map vm;
    boost::program_options::store(parse_command_line(argc, argv, desc), vm);
    boost::program_options::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << "\n";
        return "";
    }

    if (severity_debug)
        logs_init(boost::log::trivial::severity_level::debug);
    else
        logs_init(boost::log::trivial::severity_level::info);

    return host + ":" + port;
}

int main(int argc, char* argv[]) {
    std::string server_address = parse_options(argc, argv);
    if (server_address.empty())
        return 0;

    std::unique_ptr<Model> model =
            std::make_unique<TaskManager>(std::make_unique<IdGenerator>());

    GRPCServerEndPoint service { std::move(model) };

    grpc::ServerBuilder builder;
    // Listen on the given address without any authentication mechanism.
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    // Register "service" as the instance through which we'll communicate with
    // clients. In this case it corresponds to an *synchronous* service.
    builder.RegisterService(&service);
    // Finally assemble the server.
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());

    if (server) {
        LOG_TRIVIAL(info) << "Server listening on " << server_address;
    }
    else {
        LOG_TRIVIAL(error) << "Failed to start server on " << server_address;
        return 1;
    }

    // Wait for the server to shutdown. Note that some other thread must be
    // responsible for shutting down the server for this call to ever return.
    server->Wait();
}