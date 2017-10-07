/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef MACROCHECKERTEST_H
#define MACROCHECKERTEST_H

#include <gtest/gtest.h>

#include "AnalyzerLib/contentchecker/MacroChecker.h"

class MacroCheckerTest : public testing::Test
{
public:
  MacroCheckerTest()
    : testing::Test(), syntaxData1(new std::vector<unsigned char>())
  {
  }

  void SetUp() {
    for (int i = 0; i < 10; ++i) {
      this->syntaxData1->push_back(static_cast<unsigned char>(i));
    }
    this->syntaxData1->push_back('i');
    this->syntaxData1->push_back('f');
    this->syntaxData1->push_back(' ');
    this->syntaxData1->push_back('(');
    this->syntaxData1->push_back('t');
    this->syntaxData1->push_back('r');
    this->syntaxData1->push_back('u');
    this->syntaxData1->push_back('e');
    this->syntaxData1->push_back(')');
    this->syntaxData1->push_back(' ');
    this->syntaxData1->push_back('{');
    for (int i = 10; i < 20; ++i) {
      this->syntaxData1->push_back(static_cast<unsigned char>(i));
    }
  }

  virtual ~MacroCheckerTest() {
  }

  std::shared_ptr<std::vector<unsigned char>> syntaxData1;
};

TEST_F(MacroCheckerTest, init)
{
  analyzer::checker::MacroChecker checker;
  ASSERT_FALSE(checker.HasData());
}

TEST_F(MacroCheckerTest, nextSyntaxHint)
{
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->syntaxData1);
  ASSERT_EQ(checker.FindNextSyntaxHint(), 10);
}

#endif