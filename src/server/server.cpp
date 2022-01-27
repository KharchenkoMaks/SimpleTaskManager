//
// Created by Maksym Kharchenko on 25.01.2022.
//

#include "server/GRPCServerEndPoint.h"

#include "model/TaskManager.h"
#include "model/IdGenerator.h"

#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

int main() {
    std::unique_ptr<Model> model =
            std::make_unique<TaskManager>(std::make_unique<IdGenerator>());

    GRPCServerEndPoint service { std::move(model) };

    std::string server_address("0.0.0.0:8586");

    grpc::ServerBuilder builder;
    // Listen on the given address without any authentication mechanism.
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    // Register "service" as the instance through which we'll communicate with
    // clients. In this case it corresponds to an *synchronous* service.
    builder.RegisterService(&service);
    // Finally assemble the server.
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    // Wait for the server to shutdown. Note that some other thread must be
    // responsible for shutting down the server for this call to ever return.
    server->Wait();
}