#ifndef DEFINITIONSOURCETEST_H
#define DEFINITIONSOURCETEST_H

#include <gtest\gtest.h>

#include "AnalyzerLib\definitions\DefinitionSource.h"
#include "AnalyzerLib\base\error\DBException.h"

class DefinitionSourceTest : public testing::Test
{
public:
  class SomeDefSource : public analyzer::base::DefinitionSource
  {
  public:
    SomeDefSource()
      : analyzer::base::DefinitionSource()
    {
      this->setName("some_source");
    }
    virtual ~SomeDefSource(){}

    virtual bool IsInitialized() { return true; }

  
  };
};

TEST_F(DefinitionSourceTest, init)
{
  SomeDefSource defSource;
  ASSERT_TRUE(defSource.IsInitialized());
}

TEST_F(DefinitionSourceTest, GetName)
{
  SomeDefSource defSource;
  ASSERT_STREQ(defSource.GetName().c_str(), "some_source");
}

#endif