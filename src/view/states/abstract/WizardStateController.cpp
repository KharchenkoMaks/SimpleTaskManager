//
// Created by Maksym Kharchenko on 30.11.2021.
//

#include "WizardStateController.h"

WizardStateController::WizardStateController(const std::shared_ptr<Controller> &controller,
                                             const std::shared_ptr<WizardStatesFactory> &states_factory,
                                             const std::shared_ptr<ConsolePrinter> &printer,
                                             const std::shared_ptr<ConsoleReader> &reader) :
                                             WizardStateConsole(states_factory, printer, reader),
                                             controller_(controller) {

}

std::shared_ptr<Controller> WizardStateController::GetController() const {
    return controller_;
}

WizardStateController::TaskIdFromUser WizardStateController::GetTaskIdFromUser(const std::string& invitation_string) {
    std::string task_id_str = GetUserInput(invitation_string);
    try {
        WizardStateController::TaskIdFromUser answer;
        answer.task_id_ = TaskId::Create(task_id_str);
        if (GetController()->GetTask(answer.task_id_.value()) == std::nullopt) {
            answer.answer_status_ = WizardStateController::TaskIdFromUser::AnswerStatus::kNoSuchTask;
        } else {
            answer.answer_status_ = WizardStateController::TaskIdFromUser::AnswerStatus::kSuccess;
        }
        return answer;
    } catch (std::invalid_argument) {
        return WizardStateController::TaskIdFromUser
        { std::nullopt,
          WizardStateController::TaskIdFromUser::AnswerStatus::kNotValid };
    }
}
