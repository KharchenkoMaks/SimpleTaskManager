//
// Created by Maksym Kharchenko on 23.11.2021.
//

#ifndef SIMPLETASKMANAGER_ROOTSTATE_H
#define SIMPLETASKMANAGER_ROOTSTATE_H

#include "abstract/WizardStatePrinter.h"

class RootState : WizardStatePrinter {
public:
    explicit RootState(const ConsolePrinter& printer);
};


#endif //SIMPLETASKMANAGER_ROOTSTATE_H
