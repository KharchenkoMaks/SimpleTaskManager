//
// Created by Maksym Kharchenko on 30.11.2021.
//

#ifndef SIMPLETASKMANAGER_WIZARDSTATECONTROLLER_H
#define SIMPLETASKMANAGER_WIZARDSTATECONTROLLER_H

#include "WizardStateConsole.h"
#include "Controller.h"

#include <memory>
#include <optional>

class WizardStateController : public WizardStateConsole {
public:
    struct TaskIdFromUser {
        enum class AnswerStatus {
            kSuccess,
            kNotValid,
            kNoSuchTask
        };

        std::optional<TaskId> task_id_;
        AnswerStatus answer_status_;
    };
public:
    WizardStateController(const std::shared_ptr<Controller>& controller,
                          const std::shared_ptr<WizardStatesFactory>& states_factory,
                          const std::shared_ptr<ConsolePrinter>& printer,
                          const std::shared_ptr<ConsoleReader>& reader);

public:
    std::shared_ptr<Controller> GetController() const;

    // Returns std::nullopt if invalid task_id was given
    TaskIdFromUser GetTaskIdFromUser(const std::string& invitation_string = "Task ID");

private:
    std::shared_ptr<Controller> controller_;
};


#endif //SIMPLETASKMANAGER_WIZARDSTATECONTROLLER_H
