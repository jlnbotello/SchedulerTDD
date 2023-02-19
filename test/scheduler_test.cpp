#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <../inc/scheduler.hpp>
#include <functional>

#define DT_2000_01_01_00_00_00 {2000, 1, 1, 0, 0, 0}

class  MockIDatetime: public IDatetime
{
public:  
  Datetime get(){return _datetime;};
  void set(Datetime datetime){_datetime = datetime;};
private:
  Datetime _datetime;  
};

class  MockIMillis: public IMillis
{
public:
  unsigned long get(){return _millis;};
  void set(unsigned long millis){_millis = millis;};
private:
  unsigned long _millis = 0;
};

class SchedulerTest : public testing::Test
{
public: 
    using MockAction = testing::MockFunction<void(void)>;
    MockAction mockAction;
    Datetime datetime;
    MockIDatetime mockIDatetime;
    MockIMillis mockIMillis;
    TimeService timeService = {
      .iDatetime = &mockIDatetime,
      .iMillis = &mockIMillis
    };
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
  Datetime task_dt;
  DatetimeTask task = DatetimeTask("<task_name>", nullptr, task_dt);  
  
  EXPECT_CALL(mockAction, Call()).Times(0);

  task.run();
}

TEST_F(SchedulerTest, RunActionNow)
{
  Action action = std::bind(&MockAction::Call, &mockAction);
  Datetime task_dt;
  DatetimeTask task = DatetimeTask("<task_name>", &action, task_dt);  
  
  EXPECT_CALL(mockAction, Call()).Times(1);

  task.run();
}

TEST_F(SchedulerTest, DatetimeNotExpired)
{
  Action action = std::bind(&MockAction::Call, &mockAction);
  time_t rawTime;
  time(&rawTime);
  Datetime * timeInfo = localtime (&rawTime);
  //printf ("Current local time and date: %s", asctime(timeInfo));
  Datetime task_dt = (*timeInfo);
  
  DatetimeTask task = DatetimeTask("<task_name>", &action, task_dt);

  EXPECT_CALL(mockAction, Call()).Times(0);
  
  Datetime now = task_dt;
  now.tm_sec += 1; // set a difference
  mockIDatetime.set(now);

  scheduler.addTask(&task);
  task.enable();

  scheduler.run();
}

TEST_F(SchedulerTest, DatetimeExpired )
{
  Action action = std::bind(&MockAction::Call, &mockAction);
  time_t rawTime;
  time(&rawTime);
  Datetime * timeInfo = localtime (&rawTime);
  //printf ("Current local time and date: %s", asctime(timeInfo));
  Datetime task_dt = (*timeInfo);
 
  DatetimeTask task = DatetimeTask("<task_name>", &action, task_dt); 

  EXPECT_CALL(mockAction, Call()).Times(1);
  
  Datetime now = task_dt;
  mockIDatetime.set(now);

  scheduler.addTask(&task);
  task.enable();

  scheduler.run();
}

TEST_F(SchedulerTest, IntervalNotExpired)
{
  Action action = std::bind(&MockAction::Call, &mockAction);
  Interval interval_ms = 500;
  unsigned long now = interval_ms-1; // 1 ms before expiration
  int run_n_times = 2;
  
  IntervalTask task = IntervalTask("<task_name>", &action, interval_ms); 

  EXPECT_CALL(mockAction, Call()).Times(0); // never called

  scheduler.addTask(&task);
  task.enable();

  mockIMillis.set(now);

  while(run_n_times)
  {
    scheduler.run();
    run_n_times--;
  }
  
}

TEST_F(SchedulerTest, IntervalExpired)
{
  Action action = std::bind(&MockAction::Call, &mockAction);
  Interval interval_ms = 500;
  unsigned long now = interval_ms; //expired
  int run_n_times = 2;
  
  IntervalTask task = IntervalTask("<task_name>", &action, interval_ms); 

  EXPECT_CALL(mockAction, Call()).Times(1); // called once

  scheduler.addTask(&task);
  task.enable();

  mockIMillis.set(now);
  
  while(run_n_times)
  {
    scheduler.run();
    run_n_times--;
  } 
}