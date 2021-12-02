//
// Created by Maksym Kharchenko on 10.11.2021.
//

#ifndef SIMPLETASKMANAGER_TASKID_H
#define SIMPLETASKMANAGER_TASKID_H

#include <string>

class TaskId {
public:
    static TaskId Create(int id);
    static TaskId Create(const std::string& id);

    static TaskId NullTaskId();
public:
    int GetId() const;

    std::string to_string() const;
public:
    bool operator== (const TaskId& t) const;
    bool operator< (const TaskId& t) const;
private:
    explicit TaskId(int id);
    int id_;
};

#endif //SIMPLETASKMANAGER_TASKID_H
