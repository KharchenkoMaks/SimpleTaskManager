//
// Created by Maksym Kharchenko on 24.12.2021.
//

#ifndef SIMPLETASKMANAGER_CONTROLLERREQUESTRESULT_H
#define SIMPLETASKMANAGER_CONTROLLERREQUESTRESULT_H

#include "utilities/TaskActionResult.h"
#include "utilities/SaveLoadStatus.h"

#include <optional>

enum class ControllerRequestResult {
    SUCCESS,
    FAIL_NO_SUCH_TASK,
    FAIL_UNCOMPLETED_SUBTASKS,
    FAIL_NOT_DELETED_SUBTASKS,
    FAIL_INVALID_TASK,
    FILE_WAS_NOT_OPENED,
    FILE_DAMAGED
};

std::optional<ControllerRequestResult> FormControllerRequestResult(TaskActionResult result);

ControllerRequestResult FormControllerRequestResult(persistence::SaveLoadStatus result);

#endif //SIMPLETASKMANAGER_CONTROLLERREQUESTRESULT_H
