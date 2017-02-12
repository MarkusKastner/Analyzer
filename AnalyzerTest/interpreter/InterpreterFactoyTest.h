#ifndef INTERPRETERFACTORYTEST_H
#define INTERPRETERFACTORYTEST_H

#include <gtest\gtest.h>
#include "AnalyzerLib\interpreter\InterpreterFactory.h"
#include "AnalyzerLib\interpreter\ASCIIInterpreter.h"

class IntepreterFactoryTest : public testing::Test
{
public:
  IntepreterFactoryTest() 
  :simpleText()
  {}
  virtual ~IntepreterFactoryTest() {}

  void SetUp() {
    simpleText.reset(new std::vector<unsigned char>({ 'a', 'b', 'c', 'd', 'e', '~' }));
  }

  std::shared_ptr<std::vector<unsigned char>> simpleText;
};

TEST_F(IntepreterFactoryTest, emptyData)
{
  std::shared_ptr<analyzer::interpreter::Interpreter> interpreter = analyzer::interpreter::InterpreterFactory::GetInstance()->CreateInterpreter(std::shared_ptr<std::vector<unsigned char>>());
  bool success = !(!interpreter);
  ASSERT_FALSE(success);
}

TEST_F(IntepreterFactoryTest, asciiInterpreter)
{
  std::shared_ptr<analyzer::interpreter::Interpreter> interpreter = analyzer::interpreter::InterpreterFactory::GetInstance()->CreateInterpreter(simpleText);
  bool success = !(!dynamic_cast<analyzer::interpreter::ASCIIInterpreter*>(interpreter.get()));
  ASSERT_TRUE(success);
}

#endif