//
// Created by Maksym Kharchenko on 15.12.2021.
//

#ifndef SIMPLETASKMANAGER_FILEPERSISTENCE_H
#define SIMPLETASKMANAGER_FILEPERSISTENCE_H

#include "Task.pb.h"
#include "utilities/SaveLoadStatus.h"

#include "Persistence.h"

#include <vector>
#include <utility>
#include <memory>

namespace persistence {

class FilePersistence : public Persistence {
public:
    explicit FilePersistence(const std::string& file_name);
public:
    std::pair<SaveLoadStatus, std::vector<RelationalTask>> Load() override;

    SaveLoadStatus Save(const std::vector<RelationalTask>& tasks) override;
private:
    std::string file_name;
};

}

#endif //SIMPLETASKMANAGER_FILEPERSISTENCE_H
