//
// Created by Maksym Kharchenko on 02.02.2022.
//

#ifndef SIMPLETASKMANAGER_DEFAULTLOGGING_H
#define SIMPLETASKMANAGER_DEFAULTLOGGING_H

#include <boost/log/trivial.hpp>
#include <boost/log/expressions/formatters/named_scope.hpp>
#include <boost/log/utility/manipulators/add_value.hpp>

#define LOG_TRIVIAL(LEVEL) \
    BOOST_LOG_TRIVIAL(LEVEL)   \
        << boost::log::add_value("File", __FILE_NAME__) \
        << boost::log::add_value("Function", __FUNCTION__)

#endif //SIMPLETASKMANAGER_DEFAULTLOGGING_H
