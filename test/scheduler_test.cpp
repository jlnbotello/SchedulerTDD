#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <../inc/scheduler.hpp>
#include <functional>

#define DT_2000_01_01_00_00_00 {2000, 1, 1, 0, 0, 0}


class SchedulerTest : public testing::Test
{
public: 
    using MockAction = testing::MockFunction<void(void)>;
    MockAction mockAction;
    Datetime datetime = DT_2000_01_01_00_00_00;
    TimeService timeService = TimeService(datetime);
    Scheduler scheduler = Scheduler(timeService);
};

TEST_F(SchedulerTest, Basic)
{
#if BASIC_TEST_FAILS 
  EXPECT_TRUE(false);
#else
  EXPECT_TRUE(true);
#endif  
}

TEST_F(SchedulerTest, MockActionWorks)
{
  EXPECT_CALL(mockAction, Call()).Times(1);
  mockAction.Call();
}

TEST_F(SchedulerTest, RunNullActionIsSafe)
{
  //Action action = [this]() { return mockAction.Call(); };
  Action action = std::bind(&MockAction::Call, &mockAction);
  Task task = Task("RunActionNow", nullptr, nullptr, nullptr, nullptr);  
  
  EXPECT_CALL(mockAction, Call()).Times(0);

  task.run();
}

TEST_F(SchedulerTest, RunActionNow)
{
  Action action = std::bind(&MockAction::Call, &mockAction);
  Task task = Task("RunActionNow", &action, nullptr, nullptr, nullptr);  
  
  EXPECT_CALL(mockAction, Call()).Times(1);

  task.run();
}

TEST_F(SchedulerTest, ScheduleTask)
{
  Action action = std::bind(&MockAction::Call, &mockAction);
  Task task = Task("RunActionNow", &action, nullptr, nullptr, &scheduler);  
  

  scheduler.run();
}