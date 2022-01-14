//
// Created by Maksym Kharchenko on 15.12.2021.
//

#include "FilePersistence.h"

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/util/delimited_message_util.h>
#include <fstream>

using namespace persistence;

std::pair<SaveLoadStatus, std::vector<TaskTransfer>> FilePersistence::Load() {
    std::vector<TaskTransfer> loaded_tasks;

    std::ifstream file(file_name);
    if (!file.is_open()) {
        return std::make_pair(SaveLoadStatus::FILE_WAS_NOT_OPENED, loaded_tasks);
    }

    std::unique_ptr<google::protobuf::io::ZeroCopyInputStream> raw_input =
            std::make_unique<google::protobuf::io::IstreamInputStream>(&file);

    TaskTransfer read_task;
    while (google::protobuf::util::ParseDelimitedFromZeroCopyStream(&read_task, raw_input.get(), nullptr)) {
        loaded_tasks.push_back(read_task);
        read_task.clear_parent_id();
        read_task.clear_task();
        read_task.clear_task_id();
    }

    return std::make_pair(SaveLoadStatus::SUCCESS, loaded_tasks);
}

SaveLoadStatus FilePersistence::Save(const std::vector<TaskTransfer>& tasks) {

    std::ofstream file(file_name);
    if (!file.is_open()) {
        return SaveLoadStatus::FILE_WAS_NOT_OPENED;
    }

    for (const auto& task : tasks) {
        google::protobuf::util::SerializeDelimitedToOstream(task, &file);
    }

    file.close();

    return SaveLoadStatus::SUCCESS;
}

FilePersistence::FilePersistence(const std::string& file_name) : file_name(file_name) {

}
