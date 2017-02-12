/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef ASCIIINTERPRETERTEST_H
#define ASCIIINTERPRETERTEST_H

#include <gtest\gtest.h>
#include "AnalyzerLib\interpreter\ASCIIInterpreter.h"

#include <string>
#include <memory>
#include <vector>

class ASCIIInterpreterTest : public testing::Test
{
public:
  ASCIIInterpreterTest()
    :text()
  {}
  virtual ~ASCIIInterpreterTest() {}

  void SetUp() {
    text.reset(new std::vector<unsigned char>({ 'a', 'b', 'c', 'd', 'e', '~' }));
  }

  std::shared_ptr<std::vector<unsigned char>> text;
};

TEST_F(ASCIIInterpreterTest, init)
{
  analyzer::interpreter::ASCIIInterpreter interpreter;
  ASSERT_FALSE(interpreter.HasData());
}

TEST_F(ASCIIInterpreterTest, initWithData)
{
  analyzer::interpreter::ASCIIInterpreter interpreter(text);
  ASSERT_TRUE(interpreter.HasData());
}

TEST_F(ASCIIInterpreterTest, setData)
{
  analyzer::interpreter::ASCIIInterpreter interpreter;
  interpreter.SetData(text);
  ASSERT_TRUE(interpreter.HasData());
}

#endif