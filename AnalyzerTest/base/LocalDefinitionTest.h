#ifndef LOCALDEFINITIONTEST_H
#define LOCALDEFINITIONTEST_H

#include <gtest\gtest.h>

#include "AnalyzerLib\base\LocalDefinition.h"
#include "AnalyzerLib\base\error\DBException.h"

class LocalDefinitionTest : public testing::Test
{
public:

};

TEST_F(LocalDefinitionTest, init)
{
  analyzer::base::LocalDefinition localSource;
  ASSERT_TRUE(localSource.IsInitialized());
}

#endif