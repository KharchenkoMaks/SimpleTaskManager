cmake_minimum_required(VERSION 3.20)
project(SimpleTaskManager)

set(CMAKE_CXX_STANDARD 17)

include(GoogleTest)

find_package(GTest REQUIRED)
enable_testing()

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(SimpleTaskManager src/main.cpp src/model/Task.cpp src/model/Task.h src/model/TaskManager.cpp src/model/TaskManager.h src/model/TaskId.cpp src/model/TaskId.h src/model/IdGenerator.cpp src/model/IdGenerator.h)

add_executable(SimpleTaskManager_test src/model/Task.cpp src/model/Task.h tests/TaskTest.cpp)

target_link_libraries(SimpleTaskManager_test GTest::GTest GTest::Main)
