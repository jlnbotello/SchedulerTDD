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

#define MON (uint8_t)(1<<0)
#define TUE (uint8_t)(1<<1) 
#define WED (uint8_t)(1<<2)
#define THU (uint8_t)(1<<3)
#define FRI (uint8_t)(1<<4)
#define SAT (uint8_t)(1<<5)
#define SUN (uint8_t)(1<<6)

typedef union
{
  struct
  {
    uint8_t monday: 1;
    uint8_t tuesday: 1;
    uint8_t wednesday: 1;
    uint8_t thursday: 1;
    uint8_t friday: 1;
    uint8_t saturday: 1;
    uint8_t sunday: 1;
    uint8_t RESERVED: 1;
  }day;
  uint8_t mask;
}week_t;

typedef struct
{
  week_t week;
  uint8_t hour;
  uint8_t min;
  uint8_t sec;
} WeekRepeat;

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

typedef unsigned long Interval;

typedef int Repeat;

typedef struct
{
  int ocurrences;
  Datetime datetime;
  ExpirationType type;
} Expiration;

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
  virtual void enable();
  virtual void disable();
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
  IntervalTask(std::string name, Action *action, Interval interval, Repeat n);
  ~IntervalTask();    
  void init(TimeService & time_service);
  void enable();
  void disable();
  void check();
  static const int RUN_FOREVER = NEOTIMER_UNLIMITED;

private:
  Interval m_interval;
  Neotimer * m_timer = nullptr;
  Repeat m_repeat = 0;
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
  WeekdayTask(std::string name, Action *action, WeekRepeat repeat);
  void init(TimeService & time_service);
  void check();

private:
  WeekRepeat m_repeat;
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