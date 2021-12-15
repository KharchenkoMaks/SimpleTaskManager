cmake_minimum_required(VERSION 3.20)
project(SimpleTaskManager)

set(CMAKE_CXX_STANDARD 17)

include(GoogleTest)

find_package(GTest REQUIRED)
enable_testing()

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

include_directories(src/model/)
include_directories(src/view/)
include_directories(src/model/controller/)
include_directories(src/)

file(GLOB_RECURSE TaskManager_SRCS CONFIGURE_DEPENDS
        "src/view/*.h"
        "src/view/*.cpp"
        "src/model/controller/*.h"
        "src/model/controller/*.cpp"
        "src/model/*.h"
        "src/model/*.cpp"
        "src/utilities/*.h"
        "src/utilities/*.cpp"
        "src/persistence/*.h"
        "src/persistence/*.cpp")

file(GLOB_RECURSE TaskManager_TEST CONFIGURE_DEPENDS
        "tests/*.h"
        "tests/*.cpp")

#list(REMOVE_ITEM TaskManager_SRCS "main.cpp")

find_package(Protobuf REQUIRED)
message(STATUS "Using protobuf ${Protobuf_VERSION}")
find_program(_PROTOBUF_PROTOC protoc)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

file(GLOB_RECURSE PROTO_SOURCES CONFIGURE_DEPENDS src/proto/*.proto)
message("PROTO_SOURCES ${PROTO_SOURCES}")

include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS src/proto/Task.proto)
message("${PROTO_HDRS}")

add_executable(SimpleTaskManager
        ${PROTO_SRCS}
        ${PROTO_HDRS}
        ${TaskManager_SRCS}
        src/main.cpp)

add_executable(SimpleTaskManager_test
        ${PROTO_SRCS}
        ${PROTO_HDRS}
        ${TaskManager_SRCS}
        ${TaskManager_TEST})

target_link_libraries(SimpleTaskManager ${Protobuf_LIBRARIES})

target_link_libraries(SimpleTaskManager_test GTest::gtest GTest::gmock GTest::gmock_main ${Protobuf_LIBRARIES})
