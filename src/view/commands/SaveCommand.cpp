//
// Created by Maksym Kharchenko on 21.12.2021.
//

#include "SaveCommand.h"

SaveCommand::SaveCommand(const std::shared_ptr<Controller>& controller, const std::string& file_name) :
                        controller_(controller),
                        file_name_(file_name) {

}
