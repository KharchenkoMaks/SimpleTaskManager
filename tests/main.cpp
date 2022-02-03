//
// Created by Maksym Kharchenko on 03.02.2022.
//

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <boost/log/core.hpp>

int main(int argc, char** argv) {
    boost::log::core::get()->set_logging_enabled(false);
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}