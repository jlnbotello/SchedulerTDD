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
    Datetime datetime;
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
  Task task = Task("RunActionNow", nullptr, nullptr, nullptr);  
  
  EXPECT_CALL(mockAction, Call()).Times(0);

  task.run();
}

TEST_F(SchedulerTest, RunActionNow)
{
  Action action = std::bind(&MockAction::Call, &mockAction);
  Task task = Task("RunActionNow", &action, nullptr, nullptr);  
  
  EXPECT_CALL(mockAction, Call()).Times(1);

  task.run();
}

TEST_F(SchedulerTest, NotOnTimeNotTriggered)
{
  Action action = std::bind(&MockAction::Call, &mockAction);
  Datetime task_dt;
  
  Task task = Task("OneTimeAlarm", &action, &task_dt, nullptr);  //FIXME: initialize datetime with a pointer? good or bad?

  EXPECT_CALL(mockAction, Call()).Times(0);
  
  Datetime task_dt2 = task_dt;
  task_dt2.tm_sec = 10;
  timeService.setDatetime(task_dt);

  scheduler.addTask(&task);
  task.enable();

  scheduler.run();
}

TEST_F(SchedulerTest, OnTimeTriggered )
{
  Action action = std::bind(&MockAction::Call, &mockAction);
  Datetime task_dt; // <-- should be valid datetime... FIXME: init datetime
  

  Task task = Task("OneTimeAlarm", &action, &task_dt, nullptr); 

  EXPECT_CALL(mockAction, Call()).Times(1);
  
  timeService.setDatetime(task_dt);

  scheduler.addTask(&task);
  task.enable();

  scheduler.run();
}