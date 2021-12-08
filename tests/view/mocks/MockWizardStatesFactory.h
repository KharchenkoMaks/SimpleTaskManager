//
// Created by Maksym Kharchenko on 03.12.2021.
//

#ifndef SIMPLETASKMANAGER_MOCKWIZARDSTATESFACTORY_H
#define SIMPLETASKMANAGER_MOCKWIZARDSTATESFACTORY_H

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "states/factory/WizardStatesFactory.h"
#include "Controller.h"

class MockWizardStatesFactory : public WizardStatesFactory {
public:
    MockWizardStatesFactory(const std::shared_ptr<Controller>& controller,
                            const std::shared_ptr<ConsolePrinter>& printer,
                            const std::shared_ptr<ConsoleReader>& reader) :
                            WizardStatesFactory(controller, printer, reader) {}

    MOCK_METHOD(std::optional<std::shared_ptr<WizardStateConsole>>, GetNextState, (const QuitState& state, MoveType move_type), (override));
    MOCK_METHOD(std::optional<std::shared_ptr<WizardStateConsole>>, GetNextState, (const RootState& state, MoveType move_type), (override));
    MOCK_METHOD(std::optional<std::shared_ptr<WizardStateConsole>>, GetNextState, (const ShowState& state, MoveType move_type), (override));
    MOCK_METHOD(std::optional<std::shared_ptr<WizardStateConsole>>, GetNextState, (const HelpState& state, MoveType move_type), (override));
    MOCK_METHOD(std::optional<std::shared_ptr<WizardStateConsole>>, GetNextState, (const AddTaskState& state, MoveType move_type), (override));
    MOCK_METHOD(std::optional<std::shared_ptr<WizardStateConsole>>, GetNextState, (const InputTaskTitleState& state, MoveType move_type), (override));
    MOCK_METHOD(std::optional<std::shared_ptr<WizardStateConsole>>, GetNextState, (const InputTaskPriorityState& state, MoveType move_type), (override));
    MOCK_METHOD(std::optional<std::shared_ptr<WizardStateConsole>>, GetNextState, (const InputTaskDueDateState& state, MoveType move_type), (override));
    MOCK_METHOD(std::optional<std::shared_ptr<WizardStateConsole>>, GetNextState, (const AddSubTaskState& state, MoveType move_type), (override));
    MOCK_METHOD(std::optional<std::shared_ptr<WizardStateConsole>>, GetStateByCommand, (const std::string& command), (override));
};

#endif //SIMPLETASKMANAGER_MOCKWIZARDSTATESFACTORY_H
