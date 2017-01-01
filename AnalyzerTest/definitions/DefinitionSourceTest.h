#ifndef DEFINITIONSOURCETEST_H
#define DEFINITIONSOURCETEST_H

#include <gtest\gtest.h>

#include "AnalyzerLib\definitions\DefinitionSource.h"
#include "AnalyzerLib\base\error\DBException.h"

class DefinitionSourceTest : public testing::Test
{
public:
  class SomeDefSource : public analyzer::definition::DefinitionSource
  {
  public:
    SomeDefSource()
      : analyzer::definition::DefinitionSource()
    {
      this->setName("some_source");
    }
    virtual ~SomeDefSource(){}

    virtual bool IsInitialized() { return true; }
  };
  SomeDefSource defSource;
};

TEST_F(DefinitionSourceTest, init)
{
  ASSERT_TRUE(defSource.IsInitialized());
}

TEST_F(DefinitionSourceTest, GetName)
{
  ASSERT_STREQ(defSource.GetName().c_str(), "some_source");
}


#endif