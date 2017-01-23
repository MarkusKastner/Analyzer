/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

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
    : observer1(), observer2()
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

    virtual void NotifyExInterpreter() {
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
  SomeObserver observer2;
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

TEST_F(TextChangedObserverTest, UnregisterObserver)
{
  std::unique_ptr<analyzer::interpreter::Interpreter> interpreter(new analyzer::interpreter::BinaryStyleInterpreter());
  interpreter->RegisterObserver(&observer1);
  ASSERT_TRUE(interpreter->HasObservers());
  interpreter->UnregisterObserver(&observer1);
  ASSERT_FALSE(interpreter->HasObservers());
}

TEST_F(TextChangedObserverTest, InvalidObserver)
{
  std::unique_ptr<analyzer::interpreter::Interpreter> interpreter(new analyzer::interpreter::BinaryStyleInterpreter());
  std::string msg;
  try{
    interpreter->RegisterObserver(nullptr);
  }
  catch (analyzer::interpreter::InterpreterException & ex){
    msg = ex.what();
  }
  
  ASSERT_STREQ(msg.c_str(), "Invalid observer");
}

TEST_F(TextChangedObserverTest, RegisterObserverTwice)
{
  std::unique_ptr<analyzer::interpreter::Interpreter> interpreter(new analyzer::interpreter::BinaryStyleInterpreter());
  interpreter->RegisterObserver(&observer1);
  interpreter->RegisterObserver(&observer1);
  ASSERT_EQ(interpreter->NumberOfObservers(), 1);
}

TEST_F(TextChangedObserverTest, Notify)
{
  std::unique_ptr<analyzer::interpreter::Interpreter> interpreter(new analyzer::interpreter::BinaryStyleInterpreter());
  interpreter->RegisterObserver(&observer1);
  interpreter->RegisterObserver(&observer2);
  interpreter->NotifyTextChange();
  ASSERT_TRUE(observer1.IsNotified());
  ASSERT_TRUE(observer2.IsNotified());
}

#endif