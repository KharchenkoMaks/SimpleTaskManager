//
// Created by Maksym Kharchenko on 12.11.2021.
//

#ifndef SIMPLETASKMANAGER_IDGENERATOR_H
#define SIMPLETASKMANAGER_IDGENERATOR_H

#include "Task.pb.h"

/**
 * @brief \b Interface for id generators.
 */
class IdGenerator {
public:
    /**
     * @return New unique \b TaskId
     */
    virtual TaskId CreateNewTaskId() = 0;

public:
    /**
     * @brief Used to manually change last generated \b TaskId to recover it's state
     * @param task_id last generated \b TaskId
     * @warning Previously generated \b TaskIds are not guaranteed to be unique after using this method
     */
    virtual void SetLastTaskId(const TaskId& task_id) = 0;

public:
    virtual ~IdGenerator() = default;
};


#endif //SIMPLETASKMANAGER_IDGENERATOR_H
