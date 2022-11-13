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
  INTERVAL_MILISECOND,
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
    EXP_NEVER, EXP_DATE, EXP_AFTER_N
} ExpirationType;

typedef struct
{
  int second;
  int minute;
  int hour;
  int day;
  int month;
  int year;
} Datetime;


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
}	RepeatType;

class Repeat 
{
public:
  Repeat(int qty, IntervalUnit unit);


private:
  RepeatType type = REPEAT_OFF;
  bool runActionOnStart = false;
  int intervalValue;
  IntervalUnit intervalUnit;
  WeekSwitch weekSwitch;
  Expiration expiration;
};

typedef std::function<void(void)> Action;

class TimeService
{
  TimeService();
  Datetime getDatetime();
};

class Scheduler
{
public:
  Scheduler(TimeService timeSrv);
  void run();
};

class Task
{
public:
  Task(std::string name, Action* a, Datetime* dt, Repeat* r, Scheduler* s){/* FixMe: Implement me */};
  void enable();
  void disable();

};

#endif /* __SCHEDULER_HPP__ */

/*
Repeat let_repeat(1000, INTEVAL_MILISECONDS);
Task("blink_status_led", toggle_led_func, led_repeat, sched);

*/