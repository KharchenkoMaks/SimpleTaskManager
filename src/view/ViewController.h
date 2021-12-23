//
// Created by Maksym Kharchenko on 21.12.2021.
//

#ifndef SIMPLETASKMANAGER_VIEWCONTROLLER_H
#define SIMPLETASKMANAGER_VIEWCONTROLLER_H

#include "user_interface/UserInterface.h"
#include "user_interface/ConsoleStateMachine.h"

#include <memory>

class ViewController {
public:
    ViewController(std::unique_ptr<Controller> controller,
                   std::unique_ptr<UserInterface> user_interface);
public:
    void RunUserInterface();
private:
    std::unique_ptr<UserInterface> user_interface_;

    std::shared_ptr<Controller> controller_;
};


#endif //SIMPLETASKMANAGER_VIEWCONTROLLER_H
