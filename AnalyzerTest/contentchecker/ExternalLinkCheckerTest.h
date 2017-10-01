/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef EXTERNALLINKCHECKERTEST_H
#define EXTERNALLINKCHECKERTEST_H

#include <gtest/gtest.h>

#include "AnalyzerLib/contentchecker/ExternalLinkChecker.h"

class ExternalLinkCheckerTest : public testing::Test
{
public:
  ExternalLinkCheckerTest()
    : testing::Test()
  {
  }

  void SetUp() {
  }

  virtual ~ExternalLinkCheckerTest() {
  }

};

TEST_F(ExternalLinkCheckerTest, init)
{
  analyzer::checker::ExternalLinkChecker checker;
  ASSERT_FALSE(checker.HasData());
}

#endif