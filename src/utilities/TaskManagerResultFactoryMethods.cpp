//
// Created by Maksym Kharchenko on 26.01.2022.
//

#include "TaskManagerResultFactoryMethods.h"

TaskActionResult CreateTaskActionResult(const TaskManagerServiceResult& request_result) {
    switch (request_result) {
        case SUCCESS:
            return TaskActionResult::SUCCESS;
        case FAIL_NO_SUCH_TASK:
            return TaskActionResult::FAIL_NO_SUCH_TASK;
        case FAIL_INVALID_TASK:
            return TaskActionResult::FAIL_INVALID_TASK;
        case FAIL_UNCOMPLETED_SUBTASKS:
            return TaskActionResult::FAIL_UNCOMPLETED_SUBTASKS;
        case FAIL_NOT_DELETED_SUBTASKS:
            return TaskActionResult::FAIL_NOT_DELETED_SUBTASKS;
        case FAIL_NO_SUCH_LABEL:
            return TaskActionResult::FAIL_NO_SUCH_LABEL;
        default:
            return TaskActionResult::FAIL_SERVER_TROUBLES;
    }
}

TaskManagerServiceResult CreateTaskManagerServiceResult(const TaskActionResult& action_result) {
    switch (action_result) {
        case TaskActionResult::SUCCESS:
            return TaskManagerServiceResult::SUCCESS;
        case TaskActionResult::FAIL_NO_SUCH_TASK:
            return TaskManagerServiceResult::FAIL_NO_SUCH_TASK;
        case TaskActionResult::FAIL_UNCOMPLETED_SUBTASKS:
            return TaskManagerServiceResult::FAIL_UNCOMPLETED_SUBTASKS;
        case TaskActionResult::FAIL_NOT_DELETED_SUBTASKS:
            return TaskManagerServiceResult::FAIL_NOT_DELETED_SUBTASKS;
        case TaskActionResult::FAIL_INVALID_TASK:
            return TaskManagerServiceResult::FAIL_INVALID_TASK;
        case TaskActionResult::FAIL_NO_SUCH_LABEL:
            return TaskManagerServiceResult::FAIL_NO_SUCH_LABEL;
        case TaskActionResult::FAIL_SERVER_TROUBLES:
            return TaskManagerServiceResult::FAIL_SERVER_TROUBLES;
    }
}
