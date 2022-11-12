#include "module01.hpp"

Counter::Counter(int rst_val, int delta): count(rst_val), delta(delta)
{

};

void Counter::increment(int delta)
{
  count += delta;
}

void Counter::decrement(int delta)
{
  count -= delta;
}

void Counter::reset(int rst_val)
{
 count = rst_val;
}

int Counter::getCount()
{
  return count;
}