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
    MockWizardStatesFactory(const std::shared_ptr<Controller>& controller) : WizardStatesFactory(controller) {}

    MOCK_METHOD(std::optional<std::shared_ptr<WizardStateConsole>>, GetNextState, (const QuitState& state, MoveType move_type), (override));
};

#endif //SIMPLETASKMANAGER_MOCKWIZARDSTATESFACTORY_H
