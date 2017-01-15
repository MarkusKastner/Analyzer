/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef TEXTSTYLEINTERPRETERTEST_H
#define TEXTSTYLEINTERPRETERTEST_H

#include <gtest/gtest.h>

#include <string>
#include <memory>

#include "AnalyzerLib\interpreter\TextStyleInterpreter.h"
#include "AnalyzerLib\core\ByteCollection.h"
#include "AnalyzerLib\interpreter\error\InterpreterException.h"

class TextStyleInterpreterTest : public testing::Test
{
public:
  TextStyleInterpreterTest()
    :interpreter1(), interpreter2(), compare2(L"Test 100\nx")
  {}

  ~TextStyleInterpreterTest()
  {}

  void SetUp(){
    this->interpreter1.reset(new analyzer::interpreter::TextStyleInterpreter());

    std::vector<char> data2;
    data2.push_back('T');
    data2.push_back('e');
    data2.push_back('s');
    data2.push_back('t');
    data2.push_back(' ');
    data2.push_back('1');
    data2.push_back('0');
    data2.push_back('0');
    data2.push_back('\n');
    data2.push_back('x');

    std::shared_ptr<analyzer::core::ByteCollection> byteCollection2(new analyzer::core::ByteCollection(data2));
    this->interpreter2.reset(new analyzer::interpreter::TextStyleInterpreter(byteCollection2));
  }

  std::shared_ptr<analyzer::interpreter::Interpreter> interpreter1;
  std::shared_ptr<analyzer::interpreter::Interpreter> interpreter2;
  std::wstring compare2;
};

TEST_F(TextStyleInterpreterTest, InitAbstract)
{
  ASSERT_FALSE(this->interpreter1->HasData());
}

TEST_F(TextStyleInterpreterTest, GetText)
{
  ASSERT_STREQ(this->interpreter2->GetText()->c_str(), this->compare2.c_str());
}

TEST_F(TextStyleInterpreterTest, GetPlainTextOnEmptyInterpreter)
{
  analyzer::interpreter::TextStyleInterpreter interpreter;
  ASSERT_STREQ(interpreter.GetText()->c_str(), std::wstring().c_str());
}

#endif