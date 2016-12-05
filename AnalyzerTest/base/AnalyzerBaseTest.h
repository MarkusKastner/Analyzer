#ifndef ANALYZERBASETEST_H
#define ANALYZERBASETEST_H

#include <gtest\gtest.h>

#include "AnalyzerLib\base\AnalyzerBase.h"

class AnalyzerBaseTest : public testing::Test
{
public:
  AnalyzerBaseTest(){}
  ~AnalyzerBaseTest(){}

  void SetUp(){

  }
};

TEST_F(AnalyzerBaseTest, init)
{
  analyzer::base::AnalyzerBase analyzerBase;
  ASSERT_TRUE(analyzerBase.HasInterpreter());
}

TEST_F(AnalyzerBaseTest, GetInterpreter)
{
  analyzer::base::AnalyzerBase analyzerBase;
  ASSERT_TRUE(analyzerBase.Interpreter() != nullptr);
}

#endif