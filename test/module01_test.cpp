#include <gtest/gtest.h>
#include <../inc/module01.hpp>


TEST(CounterTests, Init)
{
  const int expected = 100;
  Counter counter(expected);
  int count = counter.getCount();
  EXPECT_EQ(count, expected); 
}

TEST(CounterTests, Increment)
{
  Counter counter;
  counter.increment();
  EXPECT_EQ(1, counter.getCount());
}

TEST(CounterTests, Decrement)
{
  Counter counter;
  counter.decrement();
  EXPECT_EQ(-1, counter.getCount());
}

TEST(CounterTests, Reset)
{
  Counter counter;
  counter.decrement();
  counter.reset(3);
  EXPECT_EQ(3, counter.getCount());
}
