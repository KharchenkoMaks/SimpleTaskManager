cmake_minimum_required(VERSION 3.20)
project(SimpleTaskManager)

set(CMAKE_CXX_STANDARD 17)

include(GoogleTest)

find_package(GTest REQUIRED)
enable_testing()

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

include_directories(src/model/)
include_directories(src/view/)

add_executable(SimpleTaskManager
        src/main.cpp
        src/model/tasks/Task.cpp
        src/model/tasks/Task.h
        src/model/TaskManager.cpp
        src/model/TaskManager.h
        src/model/TaskId.cpp
        src/model/TaskId.h
        src/model/IdGenerator.cpp
        src/model/IdGenerator.h
        src/model/tasks/SubTask.cpp
        src/model/tasks/SubTask.h src/view/ConsoleStateMachine.cpp src/view/ConsoleStateMachine.h src/view/WizardContext.cpp src/view/WizardContext.h src/view/states/abstract/IWizardState.h src/view/printer/ConsolePrinter.cpp src/view/printer/ConsolePrinter.h src/view/states/abstract/WizardStatePrinter.cpp src/view/states/abstract/WizardStatePrinter.h)

add_executable(SimpleTaskManager_test
        src/model/tasks/Task.cpp
        src/model/tasks/Task.h
        src/model/TaskId.cpp
        src/model/TaskId.h
        src/model/IdGenerator.cpp
        src/model/IdGenerator.h
        src/model/TaskManager.cpp
        src/model/TaskManager.h
        src/model/tasks/SubTask.h
        src/model/tasks/SubTask.cpp
        tests/model/tasks/TaskTest.cpp
        tests/model/TaskIdTest.cpp
        tests/model/IdGeneratorTest.cpp
        tests/model/TaskManagerTest.cpp
        tests/model/tasks/SubTaskTest.cpp)

target_link_libraries(SimpleTaskManager_test GTest::gtest GTest::gmock GTest::gmock_main)
