/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef RESULTTEST_H
#define RESULTTEST_H

#include <gtest/gtest.h>

#include "AnalyzerLib\strategy\Result.h"

class ResultTest : public testing::Test
{
public:
  class TextResult : public analyzer::strategy::Result
  {
  public:
    TextResult(const analyzer::strategy::Result::Classification & classification)
      :analyzer::strategy::Result(classification)
    {
    }
    virtual ~TextResult(){}
  };
};

TEST_F(ResultTest, init)
{
  TextResult res(analyzer::strategy::Result::Classification::unknown);
  ASSERT_EQ(res.GetClassification(), analyzer::strategy::Result::Classification::unknown);
}

#endif