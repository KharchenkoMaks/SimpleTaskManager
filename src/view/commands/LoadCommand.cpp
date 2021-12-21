//
// Created by Maksym Kharchenko on 21.12.2021.
//

#include "LoadCommand.h"

LoadCommand::LoadCommand(const std::shared_ptr<Controller>& controller,
                         const std::shared_ptr<ConsolePrinter>& printer,
                         const std::string& file_name) :
                         controller_(controller),
                         printer_(printer),
                         file_name_(file_name) {

}
