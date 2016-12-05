#ifndef TEXTSTYLEINTERPRETERTEST_H
#define TEXTSTYLEINTERPRETERTEST_H

#include <gtest/gtest.h>

#include <string>
#include <memory>

#include "AnalyzerLib\interpreter\TextStyleInterpreter.h"
#include "AnalyzerLib\core\ByteCollection.h"
#include "AnalyzerLib\interpreter\TextGlyph.h"
#include "AnalyzerLib\interpreter\error\InterpreterException.h"

class TextStyleInterpreterTest : public testing::Test
{
public:
  TextStyleInterpreterTest(){}
  ~TextStyleInterpreterTest(){}

  void SetUp(){

  }
};

TEST_F(TextStyleInterpreterTest, InitAbstract)
{
  std::shared_ptr<analyzer::interpreter::Interpreter> interpreter(new analyzer::interpreter::TextStyleInterpreter());
  ASSERT_FALSE(interpreter->HasData());
}

#endif