/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef EXTRAORDINARYCHECKERTEST_H
#define EXTRAORDINARYCHECKERTEST_H

#include <gtest/gtest.h>

#include "AnalyzerLib/contentchecker/ExtraOrdinaryChecker.h"

class ExtraordinaryCheckerTest : public testing::Test
{
public:
  ExtraordinaryCheckerTest()
    : testing::Test()
  {
  }

  void SetUp() {
  }

  virtual ~ExtraordinaryCheckerTest() {
  }

};

TEST_F(ExtraordinaryCheckerTest, init)
{
  analyzer::checker::ExtraordinaryChecker checker;
  ASSERT_FALSE(checker.HasData());
}

#endif