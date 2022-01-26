//
// Created by Maksym Kharchenko on 26.01.2022.
//

#ifndef SIMPLETASKMANAGER_MODELCONTROLLERRESULTCONVERTORS_H
#define SIMPLETASKMANAGER_MODELCONTROLLERRESULTCONVERTORS_H

#include "model/controller/ControllerRequestResult.h"
#include "Responses.pb.h"

ControllerRequestResult ConvertToControllerRequestResult(const ControllerRequestStatus& request_status);

ControllerRequestStatus ConvertToControllerRequestStatus(const ControllerRequestResult& controller_result);

#endif //SIMPLETASKMANAGER_MODELCONTROLLERRESULTCONVERTORS_H
