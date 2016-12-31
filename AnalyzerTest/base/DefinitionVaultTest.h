#ifndef DEFINITIONVAULTTEST_H
#define DEFINITIONVAULTTEST_H

#include <gtest\gtest.h>

#include "AnalyzerLib\base\DefinitionVault.h"
#include "AnalyzerLib\base\error\DBException.h"

class DefinitionVaultTest : public testing::Test
{
public:
  analyzer::base::DefinitionVault defSource;
};

TEST_F(DefinitionVaultTest, init)
{
  ASSERT_TRUE(defSource.HasDefinitions());
}

TEST_F(DefinitionVaultTest, NumSources)
{
  ASSERT_EQ(defSource.GetNumSources(), 1);
}

#endif