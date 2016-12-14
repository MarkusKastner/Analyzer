#ifndef ANALYZERBASETEST_H
#define ANALYZERBASETEST_H

#include <gtest\gtest.h>

#include "AnalyzerLib\base\AnalyzerBase.h"
#include "AnalyzerLib\base\AnalyzerBaseObserver.h"
#include "AnalyzerLib\base\error\AnalyzerBaseException.h"
#include "AnalyzerLib\core\File.h"

class AnalyzerBaseTest : public testing::Test
{
public:

  class SomeObserver : public analyzer::base::AnalyzerBaseObserver
  {
  public:
    SomeObserver()
      :interpreterChanged(false)
    {}
    ~SomeObserver(){}

    virtual void NotifyInterprterChange(){
      this->interpreterChanged = true;
    }
    bool InterpreterChanged(){
      return this->interpreterChanged;
    }
  private:
    bool interpreterChanged;
  };

  AnalyzerBaseTest()
    :analyzerBase1(), observer1(), path1("c:/dev/test.txt"), dummyData1()
  {}
  ~AnalyzerBaseTest(){}

  void SetUp(){
    dummyData1.push_back('D');
    dummyData1.push_back('u');
    dummyData1.push_back('m');
    dummyData1.push_back('m');
    dummyData1.push_back('y');
  }

  analyzer::base::AnalyzerBase analyzerBase1;
  SomeObserver observer1;
  std::string path1;
  std::vector<char> dummyData1;
};

TEST_F(AnalyzerBaseTest, init)
{
  ASSERT_TRUE(analyzerBase1.HasInterpreter());
}

TEST_F(AnalyzerBaseTest, GetInterpreter)
{
  ASSERT_TRUE(analyzerBase1.Interpreter() != nullptr);
}

TEST_F(AnalyzerBaseTest, SwitchMode)
{
  this->analyzerBase1.SetTextMode();
  ASSERT_TRUE(dynamic_cast<analyzer::interpreter::TextStyleInterpreter*>(this->analyzerBase1.Interpreter()));
  this->analyzerBase1.SetBinaryMode();
  ASSERT_TRUE(dynamic_cast<analyzer::interpreter::BinaryStyleInterpreter*>(this->analyzerBase1.Interpreter()));
}

TEST_F(AnalyzerBaseTest, SwitchModeWithData)
{
  ASSERT_FALSE(this->analyzerBase1.HasData());

  this->analyzerBase1.Interpreter()->ResetData(this->dummyData1);
  this->analyzerBase1.SetTextMode();
  ASSERT_TRUE(this->analyzerBase1.HasData());
  this->analyzerBase1.SetBinaryMode();
  ASSERT_TRUE(this->analyzerBase1.HasData());
}

TEST_F(AnalyzerBaseTest, HasObserver)
{
  ASSERT_EQ(this->analyzerBase1.NumberOfObservers(), 0);
}

TEST_F(AnalyzerBaseTest, RegisterObserver)
{
  this->analyzerBase1.RegisterObserver(&this->observer1);
  ASSERT_EQ(this->analyzerBase1.NumberOfObservers(), 1);
}

TEST_F(AnalyzerBaseTest, RegisterObserverTwice)
{
  this->analyzerBase1.RegisterObserver(&this->observer1);
  this->analyzerBase1.RegisterObserver(&this->observer1);
  ASSERT_EQ(this->analyzerBase1.NumberOfObservers(), 1);
}

TEST_F(AnalyzerBaseTest, UnregisterObserver)
{
  this->analyzerBase1.RegisterObserver(&this->observer1);
  ASSERT_EQ(this->analyzerBase1.NumberOfObservers(), 1);
  this->analyzerBase1.UnregisterObserver(&this->observer1);
  ASSERT_EQ(this->analyzerBase1.NumberOfObservers(), 0);
}

TEST_F(AnalyzerBaseTest, InvalidObserver)
{
  std::string message;
  try{
    this->analyzerBase1.RegisterObserver(nullptr);
  }
  catch (analyzer::base::AnalyzerBaseException & ex){
    message = ex.what();
  }
  ASSERT_STREQ(message.c_str(), "Invalid base observer");
}

TEST_F(AnalyzerBaseTest, NotifyInterpreterChanged)
{
  this->analyzerBase1.RegisterObserver(&this->observer1);
  this->analyzerBase1.SetTextMode();
  ASSERT_TRUE(this->observer1.InterpreterChanged());
}

TEST_F(AnalyzerBaseTest, EmptyHasData)
{
  ASSERT_FALSE(this->analyzerBase1.HasData());
}

TEST_F(AnalyzerBaseTest, LoadFile)
{
  this->analyzerBase1.LoadFile(this->path1);
  std::this_thread::sleep_for(std::chrono::milliseconds(200));
  ASSERT_TRUE(this->analyzerBase1.HasData());
}

TEST_F(AnalyzerBaseTest, InvalidFile)
{
  std::string message;
  std::string invalidPath("C:/dev/invalid.txt");
  try{
    this->analyzerBase1.LoadFile(invalidPath);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    this->analyzerBase1.Rethrow();
  }
  catch (analyzer::base::AnalyzerBaseException & ex){
    message = ex.what();
  }
  ASSERT_STREQ(message.c_str(), std::string("Cannot open " + invalidPath).c_str());
}

TEST_F(AnalyzerBaseTest, HasFile)
{
  analyzer::core::File analyzerFile;

  ASSERT_FALSE(this->analyzerBase1.HasFile());
}

TEST_F(AnalyzerBaseTest, AddFile)
{
  analyzer::core::File analyzerFile;

  this->analyzerBase1.AddAnalyzerFile(analyzerFile);
  ASSERT_TRUE(this->analyzerBase1.HasFile());
}

#endif