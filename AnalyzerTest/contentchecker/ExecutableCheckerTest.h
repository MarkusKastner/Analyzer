/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef EXECUTABLECHECKERTEST_H
#define EXECUTABLECHECKERTEST_H

#include <gtest/gtest.h>

#include "AnalyzerLib/contentchecker/ExecutableChecker.h"

class ExecutableCheckerTest : public testing::Test
{
public:
  ExecutableCheckerTest()
    : testing::Test()
  {
  }

  void SetUp() {
  }

  virtual ~ExecutableCheckerTest() {
  }

};

TEST_F(ExecutableCheckerTest, init)
{
  analyzer::checker::ExecutableChecker checker;
  ASSERT_FALSE(checker.HasData());
}

#endif