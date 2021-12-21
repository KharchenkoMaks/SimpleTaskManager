//
// Created by Maksym Kharchenko on 21.12.2021.
//

#include "ShowTasksCommand.h"

ShowTasksCommand::ShowTasksCommand(const std::shared_ptr<Controller>& controller,
                                   const std::shared_ptr<ConsolePrinter>& printer) :
                                   controller_(controller),
                                   printer_(printer) {

}
