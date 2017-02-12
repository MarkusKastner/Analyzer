#ifndef INTERPRETERFACTORYTEST_H
#define INTERPRETERFACTORYTEST_H

#include <gtest\gtest.h>
#include "AnalyzerLib\interpreter\InterpreterFactory.h"

class IntepreterFactoryTest : public testing::Test
{
public:
  IntepreterFactoryTest() 
  :intepreterFactory(), simpleText()
  {}
  virtual ~IntepreterFactoryTest() {}

  void SetUp() {
    simpleText.reset(new std::vector<unsigned char>({ 'a', 'b', 'c', 'd', 'e', '~' }));
  }

  analyzer::interpreter::InterpreterFactory intepreterFactory;
  std::shared_ptr<std::vector<unsigned char>> simpleText;
};

TEST_F(IntepreterFactoryTest, emptyData)
{
  ASSERT_EQ(this->intepreterFactory.CreateInterpreter(std::shared_ptr<std::vector<unsigned char>>()), nullptr);
}

#endif