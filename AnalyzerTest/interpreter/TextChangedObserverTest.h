#ifndef TEXTCHANGEDOBSERVERTEST_H
#define TEXTCHANGEDOBSERVERTEST_H

#include <gtest\gtest.h>

#include "AnalyzerLib\interpreter\TextChangedObserver.h"
#include "AnalyzerLib\interpreter\BinaryStyleInterpreter.h"
#include "AnalyzerLib\core\ByteCollection.h"

class TextChangedObserverTest : public testing::Test
{
public:
  TextChangedObserverTest()
    : observer1()
  {}

  ~TextChangedObserverTest(){}

  class SomeObserver : public analyzer::interpreter::TextChangedObserver
  {
  public:
    SomeObserver()
      :notified(false)
    {}
    virtual ~SomeObserver(){}

    virtual void NotifyDataChanged(){
      this->notified = true;
    }

    bool IsNotified(){
      return this->notified;
    }
  private:
    bool notified;
  };

  void SetUp(){

  }
  SomeObserver observer1;
};

TEST_F(TextChangedObserverTest, Init)
{
  std::unique_ptr<analyzer::interpreter::Interpreter> interpreter(new analyzer::interpreter::BinaryStyleInterpreter());
  ASSERT_FALSE(interpreter->HasObservers());
}

TEST_F(TextChangedObserverTest, RegisterObserver)
{
  std::unique_ptr<analyzer::interpreter::Interpreter> interpreter(new analyzer::interpreter::BinaryStyleInterpreter());
  interpreter->RegisterObserver(&observer1);
  ASSERT_TRUE(interpreter->HasObservers());
}

#endif