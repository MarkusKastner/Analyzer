/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef ASCIIFORMATTERTEST_H
#define ASCIIFORMATTERTEST_H

#include <gtest\gtest.h>

#include <memory>
#include <string>

#include "AnalyzerLib\interpreter\formatter\ASCIIFormatter.h"

class ASCIIFormatterTest : public testing::Test
{
public:
  ASCIIFormatterTest() : text() {}
  virtual ~ASCIIFormatterTest() {}

  virtual void SetUp() {
    this->text = "\nDer Zauberlehrling\n\nHat der alte Hexenmeister\n";
  }

  std::string text;
};

TEST_F(ASCIIFormatterTest, splitt) 
{
  std::vector<std::string> chunks(analyzer::interpreter::ASCIIFormatter::Split(this->text, 4));
  ASSERT_EQ(chunks.size(), 12);
}

TEST_F(ASCIIFormatterTest, text2Binary)
{
  std::string text("abcd");

  std::string bin(analyzer::interpreter::ASCIIFormatter::Text2BinaryExpression(text));
  ASSERT_STREQ(bin.c_str(), "01100001 01100010 01100011 01100100");
}

TEST_F(ASCIIFormatterTest, text2Numerical)
{
  std::string text("abcd");

  std::string bin(analyzer::interpreter::ASCIIFormatter::Text2NumericalExpression(text));
  ASSERT_STREQ(bin.c_str(), "97 98 99 100");
}

TEST_F(ASCIIFormatterTest, text2Hex)
{
  std::string text("abcd");

  std::string bin(analyzer::interpreter::ASCIIFormatter::Text2HexExpression(text));
  ASSERT_STREQ(bin.c_str(), "61 62 63 64");
}
#endif