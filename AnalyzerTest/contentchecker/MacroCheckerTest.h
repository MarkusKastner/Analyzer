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
    : testing::Test()
  {
  }

  void SetUp() {
  }

  virtual ~MacroCheckerTest() {
  }

};

TEST_F(MacroCheckerTest, init)
{
  analyzer::checker::MacroChecker checker;
  ASSERT_FALSE(checker.HasData());
}

#endif