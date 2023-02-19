/**
 * @file scheduler.hpp
 * @author Julian Botello (jlnbotello@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-11-13
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __SCHEDULER_HPP__
#define __SCHEDULER_HPP__

#include <functional>
#include <string>
#include <ctime>
#include <list>
#include "neotimer.hpp"

typedef struct
{
  bool Mon = false;
  bool Tue = false;
  bool Wed = false;
  bool Thu = false;
  bool Fri = false;
  bool Sat = false;
  bool Sun = false;
} WeekSwitch;

typedef struct
{
  WeekSwitch days;
  int hour;
  int min;
} Weekdays;


typedef enum
{
  INTERVAL_MICROSECOND,
  INTERVAL_MILLISECOND,
  INTERVAL_SECOND,
  INTERVAL_MINUTE,
  INTERVAL_HOUR,
  INTERVAL_DAY,
  INTERVAL_WEEK,
  INTERVAL_MONTH,
  INTERVAL_YEAR
} TimeUnit;

typedef enum
{
  EXP_NEVER,
  EXP_DATE,
  EXP_AFTER_N
} ExpirationType;

typedef struct tm Datetime;

typedef struct {
  uint32_t value;
  TimeUnit unit;
}Interval;

typedef struct
{
  int ocurrences;
  Datetime datetime;
  ExpirationType type;
} Expiration;

// typedef enum
// {
//   REPEAT_OFF,
//   REPEAT_INTERVAL,
//   REPEAT_WEEKDAYS
// } RepeatType;

// class Repeat
// {
// public:
//   Repeat(int interval, IntervalUnit unit);
//   Repeat(WeekSwitch ws, int hour, int min);

//   // private:
//   RepeatType type = REPEAT_OFF;
//   bool runActionOnStart = false;
//   int intervalValue;
//   IntervalUnit intervalUnit;
//   WeekSwitch weekSwitch;
//   Expiration expiration;
// };

using Action = std::function<void(void)>;

class IDatetime
{
  public:
    virtual ~IDatetime() {};
    virtual Datetime get() = 0;
};

typedef struct
{
  IDatetime * iDatetime;
  IMillis * iMillis;
} TimeService;

class Task
{
public:
  Task(std::string name, Action *action);
  ~Task();
  void enable();
  void disable();
  void run();
  virtual void init(TimeService & time_service) = 0;
  virtual void check() = 0;

private:
  std::string  m_name;
  Action * m_action = nullptr;  
  bool m_enabled = false;  
};

class IntervalTask: public Task
{
public:
  IntervalTask(std::string name, Action *action, Interval interval);
  ~IntervalTask();    
  void init(TimeService & time_service);
  void check();

private:
  Interval m_interval;
  Neotimer * m_timer = nullptr;
};

class DatetimeTask: public Task
{
public:
  DatetimeTask(std::string name, Action *action, Datetime datetime);
  void init(TimeService & time_service);
  void check();
private:
  Datetime m_datetime;
  IDatetime * m_iDatetime = nullptr;
};

class WeekdayTask: public Task
{
public:
  WeekdayTask(std::string name, Action *action, Weekdays weekdays);
  void init(TimeService & time_service);
  void check();

private:
  Weekdays m_weekdays;
  IDatetime * m_iDatetime = nullptr;
};

class Scheduler
{
public:
  Scheduler(TimeService & time_service);
  void run();
  bool addTask(Task * task);

private:
  std::list<Task *> m_task_list;
  TimeService & m_time_service;
};

bool operator==(Datetime dt1, Datetime dt2);

#endif /* __SCHEDULER_HPP__ */

/*
Repeat let_repeat(1000, INTEVAL_MILISECONDS);
Task("blink_status_led", toggle_led_func, led_repeat, sched);

*/