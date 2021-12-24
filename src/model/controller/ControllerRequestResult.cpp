//
// Created by Maksym Kharchenko on 24.12.2021.
//

#include "ControllerRequestResult.h"

std::optional<ControllerRequestResult> FormControllerRequestResult(TaskActionResult result) {
    switch (result) {
        case TaskActionResult::SUCCESS: {
            return ControllerRequestResult::SUCCESS;
        }
        case TaskActionResult::FAIL_NO_SUCH_TASK: {
            return ControllerRequestResult::FAIL_NO_SUCH_TASK;
        }
        case TaskActionResult::FAIL_INVALID_TASK: {
            return ControllerRequestResult::FAIL_INVALID_TASK;
        }
        default: {
            return std::nullopt;
        }
    }
}

ControllerRequestResult FormControllerRequestResult(persistence::SaveLoadStatus result) {
    switch (result) {
        case persistence::SaveLoadStatus::SUCCESS: {
            return ControllerRequestResult::SUCCESS;
        }
        case persistence::SaveLoadStatus::INVALID_FILE_STRUCTURE: {
            return ControllerRequestResult::FILE_DAMAGED;
        }
        case persistence::SaveLoadStatus::FILE_WAS_NOT_OPENED: {
            return ControllerRequestResult::FILE_WAS_NOT_OPENED;
        }
    }
}
