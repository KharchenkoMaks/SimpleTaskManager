//
// Created by Maksym Kharchenko on 21.01.2022.
//

#ifndef SIMPLETASKMANAGER_INPUTSHOWBYLABELSTATE_H
#define SIMPLETASKMANAGER_INPUTSHOWBYLABELSTATE_H

#include "states/State.h"
#include "states/factory/StatesFactory.h"
#include "user_interface/StateContext.h"
#include "Task.pb.h"

#include <memory>
#include <optional>

/* Getting task label from user
  * Used in InputShowParameters to get task label that will be used to sort tasks
  * */

class InputShowByLabelState : public State {
public:
    explicit InputShowByLabelState(const std::shared_ptr<StatesFactory>& factory);
public:
    std::shared_ptr<State> Execute(StateContext& context) override;
private:
    std::weak_ptr<StatesFactory> factory_;
};


#endif //SIMPLETASKMANAGER_INPUTSHOWBYLABELSTATE_H
