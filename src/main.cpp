#include <iostream>

#include "model/Task.h"
#include "model/TaskManager.h"

#include <vector>
#include <utility>
#include <ctime>

void PrintTaskVector(const std::vector<std::pair<int, Task>>& vec){
    for (std::pair<int, Task> item : vec){
        std::cout << "ID: " << item.first << ", " << item.second.to_string();
    }
}

int main() {
    TaskManager task_manager;
    int id1 = task_manager.Create(Task::Create("NewTask1", Task::Priority::HIGH, time(0)));
    int id2 = task_manager.Create(Task::Create("NewTask2", Task::Priority::LOW, time(0)));
    int id3 = task_manager.Create(Task::Create("NewTask3", Task::Priority::NONE, time(0)));
    task_manager.Edit(id2, Task::Create("EditedTask", Task::Priority::HIGH, time(0)));
    task_manager.Delete(id1);
    PrintTaskVector(task_manager.Show());
    return 0;
}
