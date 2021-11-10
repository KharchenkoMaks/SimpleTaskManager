//
// Created by Maksym Kharchenko on 10.11.2021.
//

#ifndef SIMPLETASKMANAGER_TASKID_H
#define SIMPLETASKMANAGER_TASKID_H

#include <string>

class TaskId {
public:
    static TaskId Create(int id);
    static TaskId Create(std::string);
    int GetId();
    bool operator== (TaskId t);
    bool operator< (TaskId t);
private:
    TaskId(int id);
    int id_;
};


#endif //SIMPLETASKMANAGER_TASKID_H
