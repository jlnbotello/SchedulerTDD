#include <gtest/gtest.h>
#include <../inc/scheduler.hpp>


TEST(SchedulerTests, LetsFail)
{
  Task TASK = Task("letsFail", nullptr, nullptr, nullptr, nullptr);
  EXPECT_TRUE(false);
}