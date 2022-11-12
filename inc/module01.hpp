#ifndef __MAIN_CPP__
#define __MAIN_CPP__

/**
 * @brief Class that keeps a count
 */

class Counter
{
public: 
  Counter(int rst_val, int inc_val);
  void increment(int delta);
  void decrement(int delta);
  void reset(int val);
};


#endif /* __MAIN_CPP__ */