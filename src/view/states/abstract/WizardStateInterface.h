//
// Created by Maksym Kharchenko on 23.11.2021.
//

#ifndef SIMPLETASKMANAGER_WIZARDSTATEINTERFACE_H
#define SIMPLETASKMANAGER_WIZARDSTATEINTERFACE_H

#include "WizardContext.h"
#include "console_io/ConsolePrinter.h"
#include "console_io/ConsoleReader.h"
#include "id/TaskId.h"

#include <memory>
#include <optional>

class WizardStateInterface {
public:
    virtual std::shared_ptr<WizardStateInterface> Execute(std::shared_ptr<WizardContext>) = 0;

public:
    virtual ~WizardStateInterface() = default;
};


#endif //SIMPLETASKMANAGER_WIZARDSTATEINTERFACE_H
