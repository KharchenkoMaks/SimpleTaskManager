//
// Created by Maksym Kharchenko on 01.02.2022.
//

#ifndef SIMPLETASKMANAGER_LOGINIT_H
#define SIMPLETASKMANAGER_LOGINIT_H

#include <boost/log/trivial.hpp>

void logs_init(boost::log::trivial::severity_level severity_level,
               bool show_in_console = true);

#endif //SIMPLETASKMANAGER_LOGINIT_H
