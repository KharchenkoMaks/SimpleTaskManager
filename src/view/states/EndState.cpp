//
// Created by Maksym Kharchenko on 09.12.2021.
//

#include "EndState.h"

EndState::EndState(const std::shared_ptr<StatesFactory>& factory) :
                    factory_(factory) {

}

std::shared_ptr<StateInterface> EndState::Execute(StateContext& context) {
    return nullptr;
}
