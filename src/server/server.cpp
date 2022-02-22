//
// Created by Maksym Kharchenko on 25.01.2022.
//

#include "server/GRPCServerEndPoint.h"

#include "model/TaskManager.h"
#include "id_generation/SequentIdGenerator.h"

#include "options/ProgramOptionsParsers.h"

#include "logs/DefaultLogging.h"

#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

int main(int argc, char* argv[]) {
    std::string server_address = parse_options_host(argc, argv, "0.0.0.0", "8586");

    std::unique_ptr<Model> model =
            std::make_unique<TaskManager>(std::make_unique<SequentIdGenerator>());

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