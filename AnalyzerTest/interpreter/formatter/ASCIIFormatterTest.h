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
#endif