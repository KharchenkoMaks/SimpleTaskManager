//
// Created by Maksym Kharchenko on 15.12.2021.
//

#include "TasksPersistence.h"

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/util/delimited_message_util.h>
#include <fstream>

using namespace persistence;

std::pair<SaveLoadStatus, TasksPersistence::TaskManagerParameters>
        TasksPersistence::LoadFromFile(const std::string& file_name) {

    TasksPersistence::TaskManagerParameters tm_parameters;

    std::ifstream file_to_read(file_name);
    if (!file_to_read.is_open()) {
        return std::make_pair(SaveLoadStatus::FILE_WAS_NOT_OPENED, tm_parameters);
    }

    std::unique_ptr<google::protobuf::io::ZeroCopyInputStream> raw_input =
            std::make_unique<google::protobuf::io::IstreamInputStream>(&file_to_read);

    if (!google::protobuf::util::ParseDelimitedFromZeroCopyStream(&tm_parameters.last_id_, raw_input.get(), nullptr)) {
        return std::make_pair(SaveLoadStatus::INVALID_FILE_STRUCTURE, tm_parameters);
    }

    TaskTransfer read_task;
    while (google::protobuf::util::ParseDelimitedFromZeroCopyStream(&read_task, raw_input.get(), nullptr)) {
        tm_parameters.tasks_.push_back(read_task);
        read_task.clear_parent_id();
        read_task.clear_task();
        read_task.clear_task_id();
    }

    return std::make_pair(SaveLoadStatus::SUCCESS, tm_parameters);
}

SaveLoadStatus TasksPersistence::SaveToFile(const std::string& file_name,
                                        const TasksPersistence::TaskManagerParameters& parameters_to_save) {

    std::ofstream file_to_write(file_name);
    if (!file_to_write.is_open()) {
        return SaveLoadStatus::FILE_WAS_NOT_OPENED;
    }
    google::protobuf::util::SerializeDelimitedToOstream(parameters_to_save.last_id_, &file_to_write);

    for (const auto& task : parameters_to_save.tasks_) {
        google::protobuf::util::SerializeDelimitedToOstream(task, &file_to_write);
    }

    file_to_write.close();

    return SaveLoadStatus::SUCCESS;
}

TasksPersistence::TaskManagerParameters::TaskManagerParameters(const TaskId& last_id,
                                                               const std::vector<TaskTransfer>& tasks) {
    last_id_.CopyFrom(last_id);
    tasks_ = tasks;
}
