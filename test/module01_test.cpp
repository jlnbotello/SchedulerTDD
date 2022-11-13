#include <gtest/gtest.h>
#include <../inc/module01.hpp>

class CounterTests : public ::testing::Test
{
protected: 
  Counter counter;

  void SetUp() override 
  {

  }

  void TearDown() override 
  {

  }
};

TEST_F(CounterTests, Init)
{
  const int expected = 0;

  int count = counter.getCount();
  
  EXPECT_EQ(expected, count); 
}

TEST_F(CounterTests, Increment)
{
  const int expected = 1;

  counter.increment();
  
  int count = counter.getCount();
  EXPECT_EQ(expected, count);
}

TEST_F(CounterTests, Decrement)
{
  const int expected = -1;

  counter.decrement();
  
  int count = counter.getCount();
  EXPECT_EQ(expected, count);
}

TEST_F(CounterTests, Reset)
{
  const int expected = -1;

  counter.decrement();
  counter.reset();
  counter.decrement();

  int count = counter.getCount();
  EXPECT_EQ(expected, count);
}
