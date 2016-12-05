#ifndef INTERPRETERSTRATEGYTEST_H
#define INTERPRETERSTRATEGYTEST_H

#include <gtest/gtest.h>
#include <memory>

#include "AnalyzerLib\interpreter\strategy\InterpretStrategyImpl.h"
#include "AnalyzerLib\core\Byte.h"

class InterpreterStrategyTest : public testing::Test
{
public:

  class MyStrategy : public analyzer::interpreter::strategy::InterpretStrategyImpl
  {
  public:
    MyStrategy()
      : analyzer::interpreter::strategy::InterpretStrategyImpl(){
    }

    MyStrategy(const std::vector<std::shared_ptr<analyzer::core::Byte>> & data)
      : analyzer::interpreter::strategy::InterpretStrategyImpl(data){
    }

    virtual std::string GetPlainText(){
      std::string text;
      for (auto& byte : this->currentData()){
        text += std::to_string(byte->GetValue());
      }
      return text;
    }

    virtual ~MyStrategy(){}
    
  };

  InterpreterStrategyTest()
    : data1(), data2(), myStrategy(), myStrategyWithData1(), myStrategyWithData2()
  {
  }

  ~InterpreterStrategyTest()
  {
  }

  void SetUp()
  {
    data1.push_back(std::shared_ptr<analyzer::core::Byte>(new analyzer::core::Byte(0)));
    myStrategyWithData1.reset(new MyStrategy(data1));

    data2.push_back(std::shared_ptr<analyzer::core::Byte>(new analyzer::core::Byte(0)));
    data2.push_back(std::shared_ptr<analyzer::core::Byte>(new analyzer::core::Byte(1)));
    data2.push_back(std::shared_ptr<analyzer::core::Byte>(new analyzer::core::Byte(2)));
    data2.push_back(std::shared_ptr<analyzer::core::Byte>(new analyzer::core::Byte(3)));
    myStrategyWithData2.reset(new MyStrategy(data2));
  }

  std::vector<std::shared_ptr<analyzer::core::Byte>> data1;
  std::vector<std::shared_ptr<analyzer::core::Byte>> data2;

  MyStrategy myStrategy;
  std::unique_ptr<MyStrategy> myStrategyWithData1;
  std::unique_ptr<MyStrategy> myStrategyWithData2;
};

TEST_F(InterpreterStrategyTest, init)
{
  ASSERT_STREQ(myStrategy.GetPlainText().c_str(), std::string("").c_str());
}

TEST_F(InterpreterStrategyTest, initByte)
{
  ASSERT_STREQ(myStrategyWithData1->GetPlainText().c_str(), std::string("0").c_str());
}

TEST_F(InterpreterStrategyTest, initByts)
{
  ASSERT_STREQ(myStrategyWithData2->GetPlainText().c_str(), std::string("0123").c_str());
}

#endif