//
// Created by Maksym Kharchenko on 16.12.2021.
//

#ifndef SIMPLETASKMANAGER_SAVELOADSTATUS_H
#define SIMPLETASKMANAGER_SAVELOADSTATUS_H

namespace persistence {

enum class SaveLoadStatus {
    SUCCESS,
    FILE_WAS_NOT_OPENED,
    INVALID_FILE_STRUCTURE
};

}

#endif //SIMPLETASKMANAGER_SAVELOADSTATUS_H
