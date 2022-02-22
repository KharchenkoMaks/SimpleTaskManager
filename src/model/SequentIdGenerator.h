//
// Created by Maksym Kharchenko on 22.02.2022.
//

#ifndef SIMPLETASKMANAGER_SEQUENTIDGENERATOR_H
#define SIMPLETASKMANAGER_SEQUENTIDGENERATOR_H

#include "IdGenerator.h"

#include <atomic>

/**
 * @brief Generating TaskIds by increment.
 * @details Threadsafety is guaranteed
 * @attention First generated TaskId will be 1
 */
class SequentIdGenerator : public IdGenerator {
public:
    SequentIdGenerator();
public:
    TaskId CreateNewTaskId() override;
public:
    void SetLastTaskId(const TaskId& task_id) override;
private:
    std::atomic<int> last_id_;
};

#endif //SIMPLETASKMANAGER_SEQUENTIDGENERATOR_H
