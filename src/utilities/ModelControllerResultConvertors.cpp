//
// Created by Maksym Kharchenko on 26.01.2022.
//

#include "ModelControllerResultConvertors.h"

ControllerRequestResult ConvertToControllerRequestResult(const ControllerRequestStatus& request_status) {
    switch (request_status) {
        case ControllerRequestStatus::SUCCESS:
            return ControllerRequestResult::SUCCESS;
        case ControllerRequestStatus::FAIL_NO_SUCH_TASK:
            return ControllerRequestResult::FAIL_NO_SUCH_TASK;
        case ControllerRequestStatus::FAIL_UNCOMPLETED_SUBTASKS:
            return ControllerRequestResult::FAIL_UNCOMPLETED_SUBTASKS;
        case ControllerRequestStatus::FAIL_NOT_DELETED_SUBTASKS:
            return ControllerRequestResult::FAIL_NOT_DELETED_SUBTASKS;
        case ControllerRequestStatus::FAIL_INVALID_TASK:
            return ControllerRequestResult::FAIL_INVALID_TASK;
        case ControllerRequestStatus::FILE_WAS_NOT_OPENED:
            return ControllerRequestResult::FILE_WAS_NOT_OPENED;
        default:
            return ControllerRequestResult::FILE_DAMAGED;
    }
}

ControllerRequestStatus ConvertToControllerRequestStatus(const ControllerRequestResult& controller_result) {
    switch (controller_result) {
        case ControllerRequestResult::SUCCESS:
            return ControllerRequestStatus::SUCCESS;
        case ControllerRequestResult::FAIL_NO_SUCH_TASK:
            return ControllerRequestStatus::FAIL_NO_SUCH_TASK;
        case ControllerRequestResult::FAIL_UNCOMPLETED_SUBTASKS:
            return ControllerRequestStatus::FAIL_UNCOMPLETED_SUBTASKS;
        case ControllerRequestResult::FAIL_NOT_DELETED_SUBTASKS:
            return ControllerRequestStatus::FAIL_NOT_DELETED_SUBTASKS;
        case ControllerRequestResult::FAIL_INVALID_TASK:
            return ControllerRequestStatus::FAIL_INVALID_TASK;
        case ControllerRequestResult::FILE_WAS_NOT_OPENED:
            return ControllerRequestStatus::FILE_WAS_NOT_OPENED;
        case ControllerRequestResult::FILE_DAMAGED:
            return ControllerRequestStatus::FILE_DAMAGED;
    }
}
