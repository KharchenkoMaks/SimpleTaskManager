//
// Created by Maksym Kharchenko on 01.02.2022.
//

#include "LogInit.h"

#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/support/date_time.hpp>

#include <iostream>

void logs_init(const bool show_in_console) {
    //boost::log::core::get()->add_global_attribute("Scope", boost::log::attributes::named_scope());

    /*auto log_format = boost::log::expressions::stream
            << "[" << boost::log::expressions::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M:%S")
            << "] [" << boost::log::expressions::format_named_scope(
            "Scope",
            boost::log::keywords::format = "%n",
            boost::log::keywords::incomplete_marker = "",
            boost::log::keywords::depth = 2)
            << "] <" << boost::log::trivial::severity
            << ">: " << boost::log::expressions::smessage;*/

    auto log_format = boost::log::expressions::stream
            << "[" << boost::log::expressions::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M:%S")
            << "] [" << boost::log::expressions::attr<std::string>("File")
            << ":" << boost::log::expressions::attr<std::string>("Function")
            << "] <" << boost::log::trivial::severity
            << ">: " << boost::log::expressions::smessage;

    boost::log::add_file_log(
            boost::log::keywords::file_name = "task_manager_%N.log",
            boost::log::keywords::rotation_size = 5 * 1024 * 1024,
            boost::log::keywords::auto_flush = true,
            boost::log::keywords::open_mode = std::ios_base::app,
            boost::log::keywords::format = log_format);

    if (show_in_console) {
        boost::log::add_console_log(
                std::cout,
                boost::log::keywords::format = log_format);
    }

    boost::log::add_common_attributes();
}
