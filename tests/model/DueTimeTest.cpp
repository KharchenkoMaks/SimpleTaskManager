//
// Created by Maksym Kharchenko on 30.11.2021.
//

#include "gtest/gtest.h"

#include "DueTime.h"

class DueTimeTest : public ::testing::Test {

};

// Creating DueTimes different ways
// Should contain right value
// GetTimeString should return right time string
TEST_F(DueTimeTest, CreatingDueTimeDifferentWays_ShouldCreateRightDueTime){
    // Arrange
    const time_t expected_time = 1638286140;
    const std::string expected_string = "17:29 30.11.2021";
    // Act
    DueTime time1 = DueTime::Create(expected_time);
    DueTime time2 = DueTime::Create(expected_string);
    const time_t actual_time1 = time1.GetTime();
    const time_t actual_time2 = time2.GetTime();
    const std::string actual_string1 = time1.GetTimeString();
    const std::string actual_string2 = time2.GetTimeString();
    // Assert
    ASSERT_EQ(time1, time2);
    EXPECT_TRUE(time1 > expected_time - 5);
    EXPECT_TRUE(time2 > expected_time - 5);
    EXPECT_EQ(expected_time, actual_time1);
    EXPECT_EQ(expected_time, actual_time2);
    EXPECT_EQ(expected_string, actual_string1);
    EXPECT_EQ(expected_string, actual_string2);
}

TEST_F(DueTimeTest, CreatingDueTimeWithIncorrectTimeString_ShouldThrowInvalidArgument){
    EXPECT_THROW(DueTime::Create("34"), std::invalid_argument);
    EXPECT_THROW(DueTime::Create("17:30"), std::invalid_argument);
    EXPECT_THROW(DueTime::Create("17:30 01.10"), std::invalid_argument);
    EXPECT_THROW(DueTime::Create("-17:30 01.10.2021"), std::invalid_argument);
    EXPECT_THROW(DueTime::Create("17:30 01.2021"), std::invalid_argument);
    EXPECT_THROW(DueTime::Create("17:30 01.10.-2021"), std::invalid_argument);
    EXPECT_THROW(DueTime::Create("17:30 01.."), std::invalid_argument);
    EXPECT_THROW(DueTime::Create("17.30 01.10.2021"), std::invalid_argument);
}