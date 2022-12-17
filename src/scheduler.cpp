#include "scheduler.hpp"


TimeService::TimeService(Datetime dt)
{

};

Datetime TimeService::getDatetime()
{
  return dt;
}

void TimeService::setDatetime(Datetime dt)
{

}

Scheduler::Scheduler(TimeService timeSrv)
{

}

void Scheduler::run()
{

}

Task::Task(std::string name, Action* a, Datetime* dt, Repeat* r, Scheduler* s)
{
  action = a;
}

void Task::run()
{
  if(action)
  {
    (*action)();
  }  
}