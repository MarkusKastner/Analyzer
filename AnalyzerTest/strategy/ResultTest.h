/** Copyright 2017 by Markus Kastner - see license details*/

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