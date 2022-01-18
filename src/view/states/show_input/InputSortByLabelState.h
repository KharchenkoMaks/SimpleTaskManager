//
// Created by Maksym Kharchenko on 17.01.2022.
//

#ifndef SIMPLETASKMANAGER_INPUTSORTBYLABELSTATE_H
#define SIMPLETASKMANAGER_INPUTSORTBYLABELSTATE_H

#include "states/State.h"
#include "states/factory/StatesFactory.h"
#include "user_interface/StateContext.h"
#include "Task.pb.h"

#include <memory>
#include <optional>

/* Getting task label from user
 * Used in InputShowParameters to get task label
 * that will be used to sort tasks
 * */

class InputSortByLabelState : public State {
public:
    explicit InputSortByLabelState(const std::shared_ptr<StatesFactory>& factory);
public:
    std::shared_ptr<State> Execute(StateContext& context) override;
private:
    std::weak_ptr<StatesFactory> factory_;
};


#endif //SIMPLETASKMANAGER_INPUTSORTBYLABELSTATE_H
