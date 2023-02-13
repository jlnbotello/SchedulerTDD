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
} IntervalUnit;

typedef enum
{
  EXP_NEVER,
  EXP_DATE,
  EXP_AFTER_N
} ExpirationType;

typedef struct tm Datetime;

typedef struct
{
  int ocurrences;
  Datetime datetime;
  ExpirationType type;
} Expiration;

typedef enum
{
  REPEAT_OFF,
  REPEAT_INTERVAL,
  REPEAT_WEEKDAYS
} RepeatType;

class Repeat
{
public:
  Repeat(int interval, IntervalUnit unit);
  Repeat(WeekSwitch ws, int hour, int min);

  // private:
  RepeatType type = REPEAT_OFF;
  bool runActionOnStart = false;
  int intervalValue;
  IntervalUnit intervalUnit;
  WeekSwitch weekSwitch;
  Expiration expiration;
};

using Action = std::function<void(void)>;

class IDatetime
{
  public:
    virtual ~IDatetime() {};
    virtual Datetime get() = 0;
};

class Task
{
public:
  //Task(std::string name, Action *a, Datetime *dt);
  Task(std::string name, Action *a, Datetime *dt, Repeat *r);  
  //Task(std::string name, Action *a, Interval *interval);
  //Task(std::string name, Action *a, Interval *interval, Repeat *r);
  ~Task();
  void setIDatetime(IDatetime * iDatetime);
  void setIMillis(IMillis * iMillis);
  void enable();
  void disable();
  void run();
  void check();

private:
  Action *action = nullptr;
  Datetime *trigDatetime = nullptr;
  Repeat *repeat = nullptr;
  Neotimer * timer = nullptr;
  IDatetime * iDatetime = nullptr;
  IMillis * iMillis = nullptr;
  bool enabled = false;

  void checkInterval();
  void checkDatetime();
  void checkWeekday();
  void init();
};

class Scheduler
{
public:
  Scheduler(IDatetime & iDatetime, IMillis & iMillis);
  void run();
  bool addTask(Task *task);

private:
  std::list<Task *> taskList;
  IDatetime & iDatetime;
  IMillis & iMillis;
};

bool operator==(Datetime dt1, Datetime dt2);

#endif /* __SCHEDULER_HPP__ */

/*
Repeat let_repeat(1000, INTEVAL_MILISECONDS);
Task("blink_status_led", toggle_led_func, led_repeat, sched);

*/