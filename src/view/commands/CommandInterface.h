//
// Created by Maksym Kharchenko on 21.12.2021.
//

#ifndef SIMPLETASKMANAGER_COMMANDINTERFACE_H
#define SIMPLETASKMANAGER_COMMANDINTERFACE_H

class CommandInterface {
public:
    virtual void Execute() = 0;
};

#endif //SIMPLETASKMANAGER_COMMANDINTERFACE_H
