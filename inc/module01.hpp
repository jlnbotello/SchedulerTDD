#ifndef __MAIN_CPP__
#define __MAIN_CPP__

/**
 * @brief Class that keeps a count
 */

class Counter
{
public: 
  Counter(int rst_val=0, int delta=1);
  void increment(int delta);
  void decrement(int delta);
  void reset(int rst_val);
  int getCount();

private:
  int count;
};


#endif /* __MAIN_CPP__ */