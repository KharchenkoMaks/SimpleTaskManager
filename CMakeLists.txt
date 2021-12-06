cmake_minimum_required(VERSION 3.20)
project(SimpleTaskManager)

set(CMAKE_CXX_STANDARD 17)

include(GoogleTest)

find_package(GTest REQUIRED)
enable_testing()

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

include_directories(src/model/)
include_directories(src/view/)
include_directories(src/controller/)
include_directories(src/)

file(GLOB_RECURSE TaskManager_SRCS CONFIGURE_DEPENDS
        "src/view/*.h"
        "src/view/*.cpp"
        "src/controller/*.h"
        "src/controller/*.cpp"
        "src/model/*.h"
        "src/model/*.cpp"
        "src/utilities/*.h"
        "src/utilities/*.cpp")

list(REMOVE_ITEM TaskManager_SRCS "main.cpp")

add_executable(SimpleTaskManager
        ${TaskManager_SRCS}
        src/main.cpp)

add_executable(SimpleTaskManager_test
        ${TaskManager_SRCS}
        tests/model/tasks/TaskTest.cpp
        tests/model/TaskIdTest.cpp
        tests/model/IdGeneratorTest.cpp
        tests/model/TaskManagerTest.cpp
        tests/model/DueTimeTest.cpp
        tests/model/tasks/SubTaskTest.cpp
        tests/view/states/StatesTests.cpp
        tests/view/mocks/MockWizardStatesFactory.h
        tests/view/mocks/MockController.h
        tests/view/mocks/MockTaskValidator.h
        tests/view/mocks/MockModel.h
        tests/view/mocks/MockConsolePrinter.h
        tests/view/mocks/MockConsoleReader.h
        tests/view/mocks/MockWizardContext.h)

target_link_libraries(SimpleTaskManager_test GTest::gtest GTest::gmock GTest::gmock_main)
