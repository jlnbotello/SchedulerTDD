#include "scheduler.hpp"

Repeat::Repeat(int interval, IntervalUnit unit)
{

}

Repeat::Repeat(WeekSwitch ws, int hour, int min)
{

}


Scheduler::Scheduler(IDatetime & iD, IMillis & iM):
iDatetime{iD}, iMillis{iM}
{

}

void Scheduler::run()
{
  std::list<Task*>::iterator it = taskList.begin();
  
    while( it != taskList.end() )
    {
      //printf("Checking task...");
      (*it)->check();
      it++;
    }
}

bool Scheduler::addTask(Task * task)
{
  task->setIDatetime(&iDatetime);
  task->setIMillis(&iMillis);

  taskList.push_back(task);
  return true;
}

Task::Task(std::string name, Action* a, Datetime* dt, Repeat* r)
{
  action = a;
  trigDatetime = dt;
}

Task::~Task()
{
 delete(timer);
}

void Task::setIDatetime(IDatetime * iD)
{
  iDatetime = iD;
}

void Task::setIMillis(IMillis * iM)
{
  iMillis = iM;
}

void Task::enable()
{
  init();
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

void Task::check()
{
  if(enabled)
  {
    RepeatType repeat_type = repeat ? (repeat->type):(REPEAT_OFF);

    switch (repeat_type)
    {
    case REPEAT_OFF:
      checkDatetime();
      break;
    case REPEAT_INTERVAL:
      checkInterval();
      break;
    case REPEAT_WEEKDAYS:
      checkWeekday();
      break;      
    default:
      /* code */
      break;
    }
  }
}

void Task::checkInterval()
{
  if(!timer) return;

  if(timer->done())
  {
      run();
  } 
}

void Task::checkDatetime()
{
  if(!trigDatetime || !iDatetime) return;
  
  if((*trigDatetime) == iDatetime->get())
  {
    run();
  }
}

void Task::checkWeekday()
{

}

void Task::init()
{
  if(!timer)
  {
    timer = new Neotimer(*iMillis);
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