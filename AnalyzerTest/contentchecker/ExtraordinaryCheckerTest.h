/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef EXTRAORDINARYCHECKERTEST_H
#define EXTRAORDINARYCHECKERTEST_H

#include <gtest/gtest.h>

#include "AnalyzerLib/contentchecker/ExtraOrdinaryChecker.h"

class ExtraOrdinaryCheckerTest : public testing::Test
{
public:
  ExtraOrdinaryCheckerTest()
    : testing::Test()
  {
  }

  void SetUp() {
  }

  virtual ~ExtraOrdinaryCheckerTest() {
  }

};

TEST_F(ExtraOrdinaryCheckerTest, init)
{
  analyzer::checker::ExtraOrdinaryChecker checker;
  ASSERT_FALSE(checker.HasData());
}

#endif