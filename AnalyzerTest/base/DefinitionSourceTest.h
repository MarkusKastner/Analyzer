#ifndef DEFINITIONSOURCETEST_H
#define DEFINITIONSOURCETEST_H

#include <gtest\gtest.h>

#include "AnalyzerLib\base\DefinitionSource.h"
#include "AnalyzerLib\base\error\DBException.h"

class DefinitionSourceTest : public testing::Test
{
public:
  class SomeDefSource : public analyzer::base::DefinitionSource
  {
  public:
    SomeDefSource()
      : analyzer::base::DefinitionSource()
    {}
    virtual ~SomeDefSource(){}

    virtual bool IsInitialized() { return true; }
  };
};

TEST_F(DefinitionSourceTest, init)
{
  SomeDefSource defSource;
  ASSERT_TRUE(defSource.IsInitialized());
}

#endif