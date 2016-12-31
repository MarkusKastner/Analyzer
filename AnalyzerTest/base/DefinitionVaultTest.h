#ifndef DEFINITIONTEST_H
#define DEFINITIONTEST_H

#include <gtest\gtest.h>

#include "AnalyzerLib\base\DefinitionVault.h"
#include "AnalyzerLib\base\error\DBException.h"

class DefinitionTest : public testing::Test
{
  
};

TEST_F(DefinitionTest, init)
{
  analyzer::base::DefinitionVault defSource;
  ASSERT_TRUE(defSource.HasDefinitions());
}

#endif