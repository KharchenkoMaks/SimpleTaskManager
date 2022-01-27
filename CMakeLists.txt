cmake_minimum_required(VERSION 3.20)
project(SimpleTaskManager)

set(CMAKE_CXX_STANDARD 17)

include(GoogleTest)

find_package(GTest REQUIRED)
enable_testing()

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined -fsanitize=nullability")

include_directories(src/model/)
include_directories(src/view/)
include_directories(src/controller/)
include_directories(src/client/)
include_directories(src/server/)
include_directories(src/)

file(GLOB_RECURSE TaskManager_SRCS CONFIGURE_DEPENDS
        "src/view/*.h"
        "src/view/*.cpp"
        "src/controller/*.h"
        "src/controller/*.cpp"
        "src/model/*.h"
        "src/model/*.cpp"
        "src/utilities/*.h"
        "src/utilities/*.cpp"
        "src/persistence/*.h"
        "src/persistence/*.cpp")

file(GLOB_RECURSE SERVER_SRCS CONFIGURE_DEPENDS
        "src/model/*.h"
        "src/model/*.cpp"
        "src/utilities/*.h"
        "src/utilities/*.cpp"
        "src/server/*.h"
        "src/server/*.cpp")

file(GLOB_RECURSE CLIENT_SRCS CONFIGURE_DEPENDS
        "src/view/*.h"
        "src/view/*.cpp"
        "src/utilities/*.h"
        "src/utilities/*.cpp"
        "src/client/*.h"
        "src/client/*.cpp"
        "src/controller/*.h"
        "src/controller/*.cpp"
        "src/persistence/*.h"
        "src/persistence/*.cpp"
        "src/model/Model.h")

file(GLOB_RECURSE TaskManager_TEST CONFIGURE_DEPENDS
        "tests/*.h"
        "tests/*.cpp")

find_package(Protobuf CONFIG REQUIRED)
message(STATUS "Using protobuf ${Protobuf_VERSION}")
find_program(_PROTOBUF_PROTOC protoc)
#

find_package(gRPC CONFIG REQUIRED)
message(STATUS "Using gRPC ${gRPC_VERSION}")
find_program(_GRPC_CPP_PLUGIN_EXECUTABLE grpc_cpp_plugin)
#

include_directories(${CMAKE_CURRENT_BINARY_DIR})

file(GLOB_RECURSE PROTO_SOURCES CONFIGURE_DEPENDS proto/*.proto)
message("PROTO_SOURCES ${PROTO_SOURCES}")

set(PROTO_DIR ${SimpleTaskManager_SOURCE_DIR}/proto)
set(GENERATED_DIR ${CMAKE_CURRENT_BINARY_DIR})

macro(compile_proto_file filename)
    get_filename_component(dirname ${filename} PATH)
    get_filename_component(basename ${filename} NAME_WE)

    message("macros ${filename}")
    add_custom_command(
            OUTPUT ${GENERATED_DIR}/${basename}.pb.cc ${GENERATED_DIR}/${basename}.grpc.pb.cc
            DEPENDS ${_PROTOBUF_PROTOC} ${PROTO_DIR}/${basename}.proto
            COMMAND ${_PROTOBUF_PROTOC} ${PROTO_DIR}/${basename}.proto
            --proto_path=${GENERATED_DIR}
            --cpp_out=${GENERATED_DIR}
            --grpc_out=generate_mock_code=true:${GENERATED_DIR}
            --plugin=protoc-gen-grpc=${_GRPC_CPP_PLUGIN_EXECUTABLE}
            -I ${PROTO_DIR}
            VERBATIM
    )
endmacro(compile_proto_file)

foreach(proto_file ${PROTO_SOURCES})
    message("compiling ${proto_file}")
    compile_proto_file(${proto_file})
    get_filename_component(basename ${proto_file} NAME_WE)
    set(task_manager_generated_files ${task_manager_generated_files} ${GENERATED_DIR}/${basename}.pb.cc ${GENERATED_DIR}/${basename}.grpc.pb.cc)
endforeach(proto_file)

include_directories(${GENERATED_DIR})

SET_SOURCE_FILES_PROPERTIES(${PROTO_SRCS} ${PROTO_HDRS} PROPERTIES GENERATED TRUE)

add_executable(SimpleTaskManager
        ${PROTO_SRCS}
        ${PROTO_HDRS}
        ${task_manager_generated_files}
        ${TaskManager_SRCS}
        src/main.cpp)

add_executable(client
        ${PROTO_SRCS}
        ${PROTO_HDRS}
        ${task_manager_generated_files}
        ${CLIENT_SRCS}
        src/client/client.cpp)

add_executable(server
        ${PROTO_SRCS}
        ${PROTO_HDRS}
        ${task_manager_generated_files}
        ${SERVER_SRCS}
        src/server/server.cpp)

add_executable(SimpleTaskManager_test
        ${PROTO_SRCS}
        ${PROTO_HDRS}
        ${task_manager_generated_files}
        ${TaskManager_SRCS}
        ${TaskManager_TEST})

target_link_libraries(SimpleTaskManager protobuf::libprotobuf gRPC::grpc++ gRPC::grpc++_reflection)
target_link_libraries(server protobuf::libprotobuf gRPC::grpc++ gRPC::grpc++_reflection)
target_link_libraries(client protobuf::libprotobuf gRPC::grpc++ gRPC::grpc++_reflection)

target_link_libraries(SimpleTaskManager_test protobuf::libprotobuf gRPC::grpc++ gRPC::grpc++_reflection GTest::gtest GTest::gmock GTest::gmock_main)
