//
// Created by Maksym Kharchenko on 23.12.2021.
//

#ifndef SIMPLETASKMANAGER_USERINTERFACE_H
#define SIMPLETASKMANAGER_USERINTERFACE_H

#include "console_io/ConsolePrinter.h"
#include "console_io/ConsoleReader.h"
#include "states/factory/StatesFactory.h"
#include "commands/CommandInterface.h"

#include <memory>
#include <string>

class UserInterface {
public:
    UserInterface(std::unique_ptr<ConsolePrinter> printer,
                  std::unique_ptr<ConsoleReader> reader,
                  const std::shared_ptr<StatesFactory>& states_factory);
public:
    std::shared_ptr<CommandInterface> AskUserForAction();
private:
    std::shared_ptr<ConsolePrinter> printer_;
    std::shared_ptr<ConsoleReader> reader_;
    std::shared_ptr<StatesFactory> states_factory_;
};


#endif //SIMPLETASKMANAGER_USERINTERFACE_H
