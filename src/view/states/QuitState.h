//
// Created by Maksym Kharchenko on 23.11.2021.
//

#ifndef SIMPLETASKMANAGER_QUITSTATE_H
#define SIMPLETASKMANAGER_QUITSTATE_H

#include "states/abstract/WizardStateConsole.h"
#include "states/factory/WizardStatesFactory.h"
#include "WizardContext.h"

#include <memory>
#include <string>

class QuitState : public WizardStateConsole {
public:
    explicit QuitState(const std::shared_ptr<ConsolePrinter>& printer,
                       const std::shared_ptr<ConsoleReader>& reader);
public:
    std::optional<std::shared_ptr<IWizardState>> Execute(std::shared_ptr<WizardContext> context,
                                          std::shared_ptr<WizardStatesFactory> state_factory) override;
private:
    bool UserConfirm();
};


#endif //SIMPLETASKMANAGER_QUITSTATE_H