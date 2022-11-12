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

}

TEST(CounterTests, Decrement)
{

}

TEST(CounterTests, Reset)
{

}
