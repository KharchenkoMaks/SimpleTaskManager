cmake_minimum_required(VERSION 3.20)
project(SimpleTaskManager)

set(CMAKE_CXX_STANDARD 17)

include(GoogleTest)

find_package(GTest REQUIRED)
enable_testing()

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

include_directories(src/model/)

add_executable(SimpleTaskManager src/main.cpp src/model/Tasks/Task.cpp src/model/Tasks/Task.h src/model/TaskManager.cpp src/model/TaskManager.h src/model/TaskId.cpp src/model/TaskId.h src/model/IdGenerator.cpp src/model/IdGenerator.h src/model/Tasks/SubTask.cpp src/model/Tasks/SubTask.h)

add_executable(SimpleTaskManager_test src/model/Tasks/Task.cpp src/model/Tasks/Task.h src/model/TaskId.cpp src/model/TaskId.h src/model/IdGenerator.cpp src/model/IdGenerator.h src/model/TaskManager.cpp src/model/TaskManager.h src/model/Tasks/SubTask.h src/model/Tasks/SubTask.cpp tests/model/Tasks/TaskTest.cpp tests/model/TaskIdTest.cpp tests/model/IdGeneratorTest.cpp tests/model/TaskManagerTest.cpp tests/model/Tasks/SubTaskTest.cpp)

target_link_libraries(SimpleTaskManager_test GTest::gtest GTest::gmock GTest::gmock_main)
