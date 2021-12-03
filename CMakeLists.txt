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

add_executable(SimpleTaskManager
        src/main.cpp
        src/model/tasks/Task.cpp
        src/model/tasks/Task.h
        src/model/TaskManager.cpp
        src/model/TaskManager.h
        src/model/id/TaskId.cpp
        src/model/id/TaskId.h
        src/model/id/IdGenerator.cpp
        src/model/id/IdGenerator.h
        src/model/tasks/SubTask.cpp
        src/model/tasks/SubTask.h
        src/view/ConsoleStateMachine.cpp
        src/view/ConsoleStateMachine.h
        src/view/WizardContext.cpp
        src/view/WizardContext.h
        src/view/console_io/ConsolePrinter.cpp
        src/view/console_io/ConsolePrinter.h
        src/view/states/abstract/WizardStateConsole.cpp
        src/view/states/abstract/WizardStateConsole.h
        src/view/states/factory/WizardStatesFactory.cpp
        src/view/states/factory/WizardStatesFactory.h
        src/view/states/RootState.cpp
        src/view/states/RootState.h
        src/view/states/HelpState.cpp
        src/view/states/HelpState.h
        src/view/states/QuitState.cpp
        src/view/states/QuitState.h
        src/view/states/task_input/AddTaskState.cpp
        src/view/states/task_input/AddTaskState.h
        src/view/states/task_input/InputTaskTitleState.cpp
        src/view/states/task_input/InputTaskTitleState.h
        src/view/states/task_input/InputTaskPriorityState.cpp
        src/view/states/task_input/InputTaskPriorityState.h
        src/view/states/task_input/InputTaskDueDateState.cpp
        src/view/states/task_input/InputTaskDueDateState.h
        src/view/states/task_input/EditTaskState.cpp
        src/view/states/task_input/EditTaskState.h
        src/view/console_io/ConsoleReader.cpp
        src/view/console_io/ConsoleReader.h
        src/controller/Controller.cpp
        src/controller/Controller.h
        src/controller/TaskValidator.cpp
        src/controller/TaskValidator.h
        src/view/states/abstract/WizardStateController.cpp
        src/view/states/abstract/WizardStateController.h
        src/view/states/ShowState.cpp
        src/view/states/ShowState.h
        src/model/DueTime.cpp
        src/model/DueTime.h
        src/model/abstract_model/IModel.h
        src/view/states/CompleteTaskState.cpp
        src/view/states/CompleteTaskState.h
        src/model/abstract_model/TaskTransfer.cpp
        src/model/abstract_model/TaskTransfer.h
        src/view/states/task_input/AddSubTaskState.cpp
        src/view/states/task_input/AddSubTaskState.h
        src/view/states/DeleteTaskState.cpp
        src/view/states/DeleteTaskState.h)

add_executable(SimpleTaskManager_test
        src/model/tasks/Task.cpp
        src/model/tasks/Task.h
        src/model/TaskManager.cpp
        src/model/TaskManager.h
        src/model/id/TaskId.cpp
        src/model/id/TaskId.h
        src/model/id/IdGenerator.cpp
        src/model/id/IdGenerator.h
        src/model/tasks/SubTask.cpp
        src/model/tasks/SubTask.h
        src/view/ConsoleStateMachine.cpp
        src/view/ConsoleStateMachine.h
        src/view/WizardContext.cpp
        src/view/WizardContext.h
        src/view/console_io/ConsolePrinter.cpp
        src/view/console_io/ConsolePrinter.h
        src/view/states/abstract/WizardStateConsole.cpp
        src/view/states/abstract/WizardStateConsole.h
        src/view/states/factory/WizardStatesFactory.cpp
        src/view/states/factory/WizardStatesFactory.h
        src/view/states/RootState.cpp
        src/view/states/RootState.h
        src/view/states/HelpState.cpp
        src/view/states/HelpState.h
        src/view/states/QuitState.cpp
        src/view/states/QuitState.h
        src/view/states/task_input/AddTaskState.cpp
        src/view/states/task_input/AddTaskState.h
        src/view/states/task_input/InputTaskTitleState.cpp
        src/view/states/task_input/InputTaskTitleState.h
        src/view/states/task_input/InputTaskPriorityState.cpp
        src/view/states/task_input/InputTaskPriorityState.h
        src/view/states/task_input/InputTaskDueDateState.cpp
        src/view/states/task_input/InputTaskDueDateState.h
        src/view/states/task_input/EditTaskState.cpp
        src/view/states/task_input/EditTaskState.h
        src/view/console_io/ConsoleReader.cpp
        src/view/console_io/ConsoleReader.h
        src/controller/Controller.cpp
        src/controller/Controller.h
        src/controller/TaskValidator.cpp
        src/controller/TaskValidator.h
        src/view/states/abstract/WizardStateController.cpp
        src/view/states/abstract/WizardStateController.h
        src/view/states/ShowState.cpp
        src/view/states/ShowState.h
        src/model/DueTime.cpp
        src/model/DueTime.h
        src/model/abstract_model/IModel.h
        src/view/states/CompleteTaskState.cpp
        src/view/states/CompleteTaskState.h
        src/model/abstract_model/TaskTransfer.cpp
        src/model/abstract_model/TaskTransfer.h
        src/view/states/task_input/AddSubTaskState.cpp
        src/view/states/task_input/AddSubTaskState.h
        src/view/states/DeleteTaskState.cpp
        src/view/states/DeleteTaskState.h
        tests/model/tasks/TaskTest.cpp
        tests/model/TaskIdTest.cpp
        tests/model/IdGeneratorTest.cpp
        tests/model/TaskManagerTest.cpp
        tests/model/DueTimeTest.cpp
        tests/model/tasks/SubTaskTest.cpp
        tests/view/states/StatesTests.cpp tests/view/mocks/MockWizardStatesFactory.h tests/view/mocks/MockController.h tests/view/mocks/MockTaskValidator.h)

target_link_libraries(SimpleTaskManager_test GTest::gtest GTest::gmock GTest::gmock_main)
