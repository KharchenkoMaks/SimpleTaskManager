//
// Created by Maksym Kharchenko on 21.12.2021.
//

#ifndef SIMPLETASKMANAGER_VIEWCONTROLLER_H
#define SIMPLETASKMANAGER_VIEWCONTROLLER_H

#include "user_interface/UserInterface.h"
#include "user_interface/ConsoleStateMachine.h"

#include <memory>

/**
 * @brief Main client side class
 * @details Running user interface and executing user's commands until user quits the program
 * @author Maksym Kharchenko
 */
class ViewController {
public:
    ViewController(std::unique_ptr<ModelController> controller,
                   std::unique_ptr<UserInterface> user_interface);
public:
    /**
     * Starting loop of asking user for command and executing it
     * @attention Method will be running until user quits the program
     */
    void RunUserInterface();
private:
    std::unique_ptr<UserInterface> user_interface_;

    std::shared_ptr<ModelController> controller_;
};


#endif //SIMPLETASKMANAGER_VIEWCONTROLLER_H
