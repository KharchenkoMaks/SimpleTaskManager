//
// Created by Maksym Kharchenko on 02.02.2022.
//

#ifndef SIMPLETASKMANAGER_DEFAULTLOGGING_H
#define SIMPLETASKMANAGER_DEFAULTLOGGING_H

#include <boost/log/trivial.hpp>
#include <boost/log/expressions/formatters/named_scope.hpp>
#include <boost/log/utility/manipulators/add_value.hpp>

#ifdef __FILE_NAME__

#define LOG_TRIVIAL(LEVEL) \
    BOOST_LOG_TRIVIAL(LEVEL)   \
        << boost::log::add_value("File", __FILE_NAME__) \
        << boost::log::add_value("Function", __FUNCTION__)

#else

#define LOG_TRIVIAL(LEVEL) \
    BOOST_LOG_TRIVIAL(LEVEL)   \
        << boost::log::add_value("File", __FILE__) \
        << boost::log::add_value("Function", __FUNCTION__)

#endif

#endif //SIMPLETASKMANAGER_DEFAULTLOGGING_H
