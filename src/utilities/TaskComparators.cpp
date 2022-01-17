//
// Created by Maksym Kharchenko on 23.12.2021.
//

#include "TaskComparators.h"

bool operator<(const TaskId& task_id1, const TaskId& task_id2) {
    return task_id1.id() < task_id2.id();
}

bool operator==(const TaskId& task_id1, const TaskId& task_id2) {
    return task_id1.id() == task_id2.id();
}

bool operator==(const Task& task1, const Task& task2) {
    return task1.title() == task2.title() &&
           task1.priority() == task2.priority() &&
           task1.due_date() == task2.due_date() &&
           task1.completed() == task2.completed() &&
           task1.label() == task2.label();
}

bool operator==(const RelationalTask& task1, const RelationalTask& task2) {
    return task1.task_id() == task2.task_id() &&
           task1.task() == task2.task() &&
           task1.parent_id() == task2.parent_id();
}
