//
// Created by Maksym Kharchenko on 23.11.2021.
//

#ifndef SIMPLETASKMANAGER_WIZARDCONTEXT_H
#define SIMPLETASKMANAGER_WIZARDCONTEXT_H

#include "tasks/Task.h"

#include <memory>
#include <string>
#include <optional>
#include <ctime>

class WizardContext {
public:
    enum class ConfirmationStatus{
        kConfirmed,
        kNotConfirmed,
        kNone
    };
public:
    WizardContext();
public: // User confirmation information
    void ConfirmAction();
    void NotConfirmAction();
    void ResetActionConfirmation();
    ConfirmationStatus GetConfirmationStatus();

    void SetConfirmMessage(const std::string& message);
    void ResetConfirmMessage();
    std::optional<std::string> GetConfirmMessage();
public: // StateMachine interruption information
    void InterruptStateMachine();
    bool IsStateMachineStopped();
public: // Adding task information
    void AddTaskTitle(const std::string& title);
    void AddTaskPriority(Task::Priority priority);
    void AddTaskDueTime(time_t due_time);
    void AddTask(const Task& task);
    std::optional<Task> GetAddedTask();
    void ResetAddedTask();
private:
    Task CreateDefaultTask();
    void AddedTaskInitialize();
private:
    bool state_machine_stopped_;

    ConfirmationStatus confirmation_;
    std::optional<std::string> confirm_message_;

    std::optional<Task> added_task_;
};


#endif //SIMPLETASKMANAGER_WIZARDCONTEXT_H
