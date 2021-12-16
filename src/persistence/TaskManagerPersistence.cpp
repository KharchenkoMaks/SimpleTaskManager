//
// Created by Maksym Kharchenko on 15.12.2021.
//

#include "TaskManagerPersistence.h"

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/util/delimited_message_util.h>
#include <fstream>

TaskManagerPersistence::TaskManagerParameters TaskManagerPersistence::LoadFromFile(const std::string& file_name) {
    TaskManagerPersistence::TaskManagerParameters tm_parameters;

    std::ifstream file_to_read(file_name);

    std::unique_ptr<google::protobuf::io::ZeroCopyInputStream> raw_input =
            std::make_unique<google::protobuf::io::IstreamInputStream>(&file_to_read);

    google::protobuf::util::ParseDelimitedFromZeroCopyStream(&tm_parameters.last_id_, raw_input.get(), nullptr);

    TaskTransfer read_task;
    while (google::protobuf::util::ParseDelimitedFromZeroCopyStream(&read_task, raw_input.get(), nullptr)) {
        tm_parameters.tasks_.push_back(read_task);
        read_task.clear_parent_id();
        read_task.clear_task();
        read_task.clear_task_id();
    }

    return tm_parameters;
}

bool TaskManagerPersistence::SaveToFile(const std::string& file_name,
                                        const TaskManagerPersistence::TaskManagerParameters& parameters_to_save) {

    std::ofstream file_to_write(file_name);
    google::protobuf::util::SerializeDelimitedToOstream(parameters_to_save.last_id_, &file_to_write);

    for (const auto& task : parameters_to_save.tasks_) {
        google::protobuf::util::SerializeDelimitedToOstream(task, &file_to_write);
    }

    file_to_write.close();

    return true;
}
