//
// Created by Maksym Kharchenko on 20.12.2021.
//

#ifndef SIMPLETASKMANAGER_CONSOLEUTILITIES_H
#define SIMPLETASKMANAGER_CONSOLEUTILITIES_H

#include "user_interface/console_io/ConsoleReader.h"
#include "user_interface/console_io/ConsolePrinter.h"
#include "Task.pb.h"
#include "utilities/TaskConvertors.h"

#include <string>
#include <optional>

namespace console_io::util {

std::string GetUserInput(const std::string& invitation_message, const ConsolePrinter& printer, const ConsoleReader& reader);

bool UserConfirm(const std::string &question_string, const ConsolePrinter& printer, const ConsoleReader& reader);

std::optional<TaskId> GetTaskIdFromUser(const std::string& invitation_string, const ConsolePrinter& printer, const ConsoleReader& reader);

}
#endif //SIMPLETASKMANAGER_CONSOLEUTILITIES_H
