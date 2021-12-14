//
// Created by Maksym Kharchenko on 14.12.2021.
//

#include "MainTask.h"

MainTask::MainTask(const Task& task) {
    task_.CopyFrom(task);
}

MainTask MainTask::Create(const Task& task) {
    return MainTask(task);
}

void MainTask::AddSubTask(const TaskId& task_id, const Task& subtask) {
    subtasks_.insert_or_assign(task_id, subtask);
}

bool MainTask::ContainsSubTask(const TaskId& subtask_id) {
    return subtasks_.find(subtask_id) != subtasks_.end();
}
