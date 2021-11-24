//
// Created by Maksym Kharchenko on 23.11.2021.
//

#ifndef SIMPLETASKMANAGER_WIZARDSTATESFACTORY_H
#define SIMPLETASKMANAGER_WIZARDSTATESFACTORY_H

#include "states/abstract/IWizardState.h"
#include "printer/ConsolePrinter.h"

#include "states/RootState.h"
#include "states/HelpState.h"
#include "states/quit/QuitState.h"
#include "states/confirm/ConfirmState.h"

#include <memory>
#include <string>

class RootState;
class HelpState;
class QuitState;
class ConfirmState;

class WizardStatesFactory {
public:
    WizardStatesFactory();
    std::shared_ptr<IWizardState> GetStateByCommand(const std::string& command);

    std::shared_ptr<RootState> GetRootState();
    std::shared_ptr<QuitState> GetQuitState();
    std::shared_ptr<ConfirmState> GetConfirmState();
private:
    std::shared_ptr<RootState> root_state_;
    std::shared_ptr<HelpState> help_state_;
    std::shared_ptr<QuitState> quit_state_;
    std::shared_ptr<ConfirmState> confirm_state_;

    std::shared_ptr<ConsolePrinter> printer_;
};


#endif //SIMPLETASKMANAGER_WIZARDSTATESFACTORY_H
