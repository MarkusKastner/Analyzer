#ifndef DEFINITIONVAULTTEST_H
#define DEFINITIONVAULTTEST_H

#include <gtest\gtest.h>

#include "AnalyzerLib\base\DefinitionVault.h"
#include "AnalyzerLib\base\error\DBException.h"

class DefinitionVaultTest : public testing::Test
{
  
};

TEST_F(DefinitionVaultTest, init)
{
  analyzer::base::DefinitionVault defSource;
  ASSERT_TRUE(defSource.HasDefinitions());
}

#endif