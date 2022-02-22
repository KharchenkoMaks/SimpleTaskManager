//
// Created by Maksym Kharchenko on 20.12.2021.
//

#include "ConsoleUtilities.h"

namespace console_io::util {

std::string GetUserInput(const std::string& invitation_message, const ConsolePrinter& printer, const ConsoleReader& reader) {
    printer.Write(invitation_message + "> ");
    std::string user_input = reader.ReadLine();
    return user_input;
}

bool UserConfirm(const std::string& question_string, const ConsolePrinter& printer, const ConsoleReader& reader) {
    std::string users_answer = GetUserInput(question_string + " y/n", printer, reader);
    return users_answer == "Y" || users_answer == "y";
}

std::optional<TaskId> GetTaskIdFromUser(const std::string& invitation_string, const ConsolePrinter& printer, const ConsoleReader& reader) {
    std::string task_id_str = GetUserInput(invitation_string, printer, reader);
    return StringToTaskId(task_id_str);
}

}