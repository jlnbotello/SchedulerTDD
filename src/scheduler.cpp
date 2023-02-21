#include "scheduler.hpp"

Scheduler::Scheduler(TimeService & time_service)
:m_time_service{time_service}
{

}

void Scheduler::run()
{
  std::list<Task*>::iterator it = m_task_list.begin();
  
    while( it != m_task_list.end() )
    {
      (*it)->check();
      it++;
    }
}

bool Scheduler::addTask(Task * task)
{
  task->init(m_time_service);
  m_task_list.push_back(task);
  return true;
}

Task::Task(std::string name, Action *action)
{
  m_name = name;
  m_action = action;
}

Task::~Task()
{

}

void Task::enable()
{
  m_enabled = true;
}

void Task::disable()
{
  m_enabled = false;
}

void Task::run()
{
  if(m_action)
  {
    (*m_action)();
  }  
}

IntervalTask::IntervalTask(std::string name, Action *action, Interval interval)
:Task(name, action)
{
  m_interval = interval;
}

IntervalTask::IntervalTask(std::string name, Action *action, Interval interval, Repeat n)
:IntervalTask(name, action, interval)
{
  m_interval = interval;
  m_repeat = n;
}

IntervalTask::~IntervalTask()
{
  delete(m_timer);
}

void IntervalTask::enable()
{
  Task::enable();
  m_timer->start();

}

void IntervalTask::disable()
{
  Task::disable();
  m_timer->stop();
}

void IntervalTask::init(TimeService & time_service)
{
  if(m_timer){return;}
  m_timer = new Neotimer(*time_service.iMillis, m_interval);
}

void IntervalTask::check()
{
  if(!m_timer) return;
  if(!!m_repeat)
  {
    if(m_timer->repeat(m_repeat))
    {
        run();
    }
  }
  else
  {
    if(m_timer->done())
    {
        run();
        disable();
    }
  }
}

DatetimeTask::DatetimeTask(std::string name, Action *action, Datetime datetime)
:Task(name, action)
{
  m_datetime = datetime;
}

void DatetimeTask::init(TimeService & time_service)
{
 m_iDatetime = time_service.iDatetime;
}

void DatetimeTask::check()
{
  if(!m_iDatetime) return;
  
  if((m_datetime) == m_iDatetime->get())
  {
    run();
  }
}

WeekdayTask::WeekdayTask(std::string name, Action *action, WeekRepeat repeat)
:Task(name, action)
{
  m_repeat = repeat;
}

void WeekdayTask::init(TimeService & time_service)
{
 m_iDatetime = time_service.iDatetime;
}

void WeekdayTask::check()
{  
  if(!m_iDatetime) return;

  uint8_t week_mask = SUN; 
  Datetime now =  m_iDatetime->get();
  
  if(now.tm_wday > 0)
  {
    week_mask = (uint8_t)(1 << (now.tm_wday-1));
  }
  
  if((week_mask & m_repeat.week.mask) &&
     (now.tm_hour == m_repeat.hour) &&
     (now.tm_min == m_repeat.min) &&
     (now.tm_sec == m_repeat.sec))
  {
    run();
  }    
}

bool operator==(Datetime dt1, Datetime dt2)
{
  time_t seconds1 = mktime(&dt1);
  time_t seconds2 = mktime(&dt1);
  
  // cannot be represented -> safer
  if((seconds1 == -1) || (seconds2 == -1))
    return false;

  if(difftime(mktime(&dt1), mktime(&dt2)) == 0)
  {
    return true;
  }
  return false;
}