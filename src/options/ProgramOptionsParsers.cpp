//
// Created by Maksym Kharchenko on 07.02.2022.
//

#include "ProgramOptionsParsers.h"

#include "logs/LogInit.h"

#include <boost/program_options.hpp>

#include <iostream>

std::string parse_options_host(int argc, char* argv[], const std::string& default_host, const std::string& default_port) {
    bool show_logs_in_console = false;
    bool severity_debug = false;
    std::string host = default_host;
    std::string port = default_port;

    const std::string host_help_message = "server host, default" + default_host;

    boost::program_options::options_description desc("Allowed options");

    desc.add_options()
            ("log_console", boost::program_options::bool_switch(&show_logs_in_console), "show logs in console")
            ("debug", boost::program_options::bool_switch(&severity_debug), "enable debug logs")
            ("host", boost::program_options::value(&host), "server host")
            ("port", boost::program_options::value(&port), "server port");

    boost::program_options::variables_map vm;
    boost::program_options::store(parse_command_line(argc, argv, desc), vm);
    boost::program_options::notify(vm);

    logs_init(severity_debug ? boost::log::trivial::severity_level::debug : boost::log::trivial::severity_level::info, show_logs_in_console);

    return host + ":" + port;
}
