//
// Created by Maksym Kharchenko on 14.01.2022.
//

#ifndef SIMPLETASKMANAGER_PERSISTENCEFACTORY_H
#define SIMPLETASKMANAGER_PERSISTENCEFACTORY_H

#include "Persistence.h"

#include <memory>

namespace persistence {

class PersistenceFactory {
public:
    std::unique_ptr<persistence::Persistence> CreateFilePersistence(const std::string& file_name);
};

}


#endif //SIMPLETASKMANAGER_PERSISTENCEFACTORY_H
