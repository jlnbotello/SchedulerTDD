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
  std::list<Task*>::iterator it = taskList.begin();

    Datetime now = timeService.getDatetime();
    while( it != taskList.end() )
    {
      //printf("Checking task...");
      (**it).check(now);
      it++;
    }
}

bool Scheduler::addTask(Task * task)
{
  taskList.push_back(task);
  return true;
}

Task::Task(std::string name, Action* a, Datetime* dt, Repeat* r)
{
  action = a;
  trigDatetime = dt;
}

void Task::enable()
{
  enabled = true;
}

void Task::disable()
{
  enabled = false;
}


void Task::run()
{
  if(action)
  {
    (*action)();
  }  
}

void Task::check(Datetime currDatetime)
{
  if(enabled && action && trigDatetime)
  {
    if((*trigDatetime) == currDatetime)
    {
      run();
    }
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