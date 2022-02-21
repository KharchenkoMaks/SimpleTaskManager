//
// Created by Maksym Kharchenko on 01.12.2021.
//

#ifndef SIMPLETASKMANAGER_MODEL_H
#define SIMPLETASKMANAGER_MODEL_H

#include "Task.pb.h"
#include "utilities/TaskActionResult.h"
#include "IdGenerator.h"

#include <optional>
#include <utility>

class Model {
public:
    /**
     * @param task Protobuf Task message to add
     * @return std::pair: enum TaskActionResult, TaskId of added Task, if task was added
     */
    virtual std::pair<TaskActionResult, TaskId> AddTask(const Task& task) = 0;
    /**
     * @param task Protobuf Task message to add
     * @param parent_id Protobuf TaskId of parent Task
     * @return std::pair: enum TaskActionResult, TaskId of added SubTask, if it was added
     */
    virtual std::pair<TaskActionResult, TaskId> AddSubTask(const Task& task, const TaskId& parent_id) = 0;
    /**
     * Swaps current task with specified id with new one.
     * @param id TaskId of task to update
     * @param t New task
     * @return enum TaskActionResult
     */
    virtual TaskActionResult EditTask(const TaskId& id, const Task& t) = 0;
    /**
     * @param id TaskId to delete
     * @param force_delete_subtasks confirm for deleting all subtasks of deleted task if there are some
     * @return enum TaskActionResult
     * @attention If \b force_delete_subtasks set to false and target task has subtasks,
     * deleting will be failed
     */
    virtual TaskActionResult DeleteTask(const TaskId& id, bool force_delete_subtasks) = 0;
    /**
     * @param id TaskId to complete
     * @param force_complete_subtasks confirm for completing all subtasks of deleted task if there are some uncompleted
     * @return enum TaskActionResult
     * @attention If \b force_complete_subtasks set to false and target task has \b uncompleted subtasks,
     * completing will be failed
     */
    virtual TaskActionResult CompleteTask(const TaskId& id, bool force_complete_subtasks) = 0;
    /**
     * @param id TaskId of task for adding label
     * @param label Label to add
     * @return enum TaskActionResult
     */
    virtual TaskActionResult AddTaskLabel(const TaskId& id, const std::string& label) = 0;
    /**
     * @param id TaskId of task to remove label from
     * @param label Label to remove
     * @return enum TaskActionResult
     */
    virtual TaskActionResult RemoveTaskLabel(const TaskId& id, const std::string& label) = 0;

    /**
     * @return All not deleted \b tasks as \b std::vector
     * @attention Order of tasks in \b std::vector is not guaranteed
     */
    virtual std::vector<RelationalTask> GetTasks() = 0;
    /**
     * @param task_label Label to sort tasks by
     * @return All not deleted \b tasks as \b std::vector, that contains specified \b task_label
     * @attention Order of tasks in \b std::vector is not guaranteed
     */
    virtual std::vector<RelationalTask> GetTasksByLabel(const std::string& task_label) = 0;
    /**
     * @param task_id TaskId of task to get
     * @return RelationalTask if task with specified \b task_id was found
     */
    virtual std::optional<RelationalTask> GetTask(const TaskId& task_id) = 0;

    /**
     * Loads new tasks to model and deletes all previous tasks
     * @param tasks Tasks to load to model
     * @return Whether tasks were loaded successfully
     * @attention Loading of new model state leads to losing it's previous state.
     * @attention If loading of new state fails, previous state is remaining untouched.
     */
    virtual bool LoadModelState(const std::vector<RelationalTask>& tasks) = 0;

    virtual ~Model() = default;
};

#endif //SIMPLETASKMANAGER_MODEL_H
