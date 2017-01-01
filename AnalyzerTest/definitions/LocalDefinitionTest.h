#ifndef LOCALDEFINITIONTEST_H
#define LOCALDEFINITIONTEST_H

#include <gtest\gtest.h>

#include "AnalyzerLib\definitions\LocalDefinition.h"

#include "AnalyzerLib\base\error\DBException.h"

class LocalDefinitionTest : public testing::Test
{
public:

};

TEST_F(LocalDefinitionTest, init)
{
  analyzer::definition::LocalDefinition localSource;
  ASSERT_TRUE(localSource.IsInitialized());
}

TEST_F(LocalDefinitionTest, initNamedResource)
{
  analyzer::definition::LocalDefinition localSource("source_name");
  ASSERT_STREQ(localSource.GetName().c_str(), "source_name");
}

#endif