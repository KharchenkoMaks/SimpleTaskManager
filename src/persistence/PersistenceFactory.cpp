//
// Created by Maksym Kharchenko on 14.01.2022.
//

#include "PersistenceFactory.h"

#include "FilePersistence.h"

std::unique_ptr<persistence::Persistence> persistence::PersistenceFactory::CreateFilePersistence(const std::string& file_name) {
    return std::make_unique<FilePersistence>(file_name);
}
