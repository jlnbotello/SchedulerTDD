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
  this->dt = dt;
}

Scheduler::Scheduler(TimeService & timeSrv):timeService{timeSrv}
{

}

void Scheduler::run()
{
  std::list<Task>::iterator it = taskList.begin();

    Datetime now = timeService.getDatetime();
    while( it != taskList.end() )
    {
      (*it).run(now);
    }
}

bool Scheduler::addTask( Task task)
{
  taskList.push_back(task);
  return true;
}

Task::Task(std::string name, Action* a, Datetime* dt, Repeat* r)
{
  action = a;
  datetime = dt;
}

void Task::run()
{
  if(action)
  {
    (*action)();
  }  
}

void Task::run(Datetime dt)
{

}