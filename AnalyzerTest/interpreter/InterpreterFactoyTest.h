#ifndef INTERPRETERFACTORYTEST_H
#define INTERPRETERFACTORYTEST_H

#include <gtest\gtest.h>
#include "AnalyzerLib\interpreter\InterpreterFactory.h"
#include "AnalyzerLib\interpreter\ASCIIInterpreter.h"
#include "AnalyzerLib\interpreter\XMLInterpreter.h"
#include "AnalyzerLib\interpreter\BMPInterpreter.h"

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

TEST_F(IntepreterFactoryTest, xmlInterpreter)
{
  std::string fileData("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\" ?>\n<tag1>\n  <tag2>some text</tag2>\n  <tag3/>\n</tag1>");
  std::shared_ptr<std::vector<unsigned char>> data(new std::vector<unsigned char>(fileData.begin(), fileData.end()));
  std::shared_ptr<analyzer::interpreter::Interpreter> interpreter = analyzer::interpreter::InterpreterFactory::GetInstance()->CreateInterpreter(data);
  bool success = !(!dynamic_cast<analyzer::interpreter::XMLInterpreter*>(interpreter.get()));
  ASSERT_TRUE(success);
}

TEST_F(IntepreterFactoryTest, bmpInterpreter)
{
  std::shared_ptr<std::vector<unsigned char>> data = TestSupport::GetInstance()->GetDataFromTestFilesDir("bmp/test16_1.bmp");
  std::shared_ptr<analyzer::interpreter::Interpreter> interpreter = analyzer::interpreter::InterpreterFactory::GetInstance()->CreateInterpreter(data);
  bool success = !(!dynamic_cast<analyzer::interpreter::BMPInterpreter*>(interpreter.get()));
  ASSERT_TRUE(success);
}

//BMPInterpreter
//HEXInterpreter
#endif