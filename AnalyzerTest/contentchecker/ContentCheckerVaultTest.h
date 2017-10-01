/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef CONTENTCHECKERVAULTTEST_H
#define CONTENTCHECKERVAULTTEST_H

#include <gtest/gtest.h>

#include "AnalyzerLib/contentchecker/ContentCheckerVault.h"
#include "AnalyzerLib/contentchecker/ExtraordinaryChecker.h"
#include "AnalyzerLib/contentchecker/ExecutableChecker.h"
#include "AnalyzerLib/contentchecker/ExternalLinkChecker.h"
#include "AnalyzerLib/contentchecker/MacroChecker.h"

class ContentCheckerVaultTest : public testing::Test
{
public:
  ContentCheckerVaultTest()
    : testing::Test(), contentCheckerVault()
  {
  }

  void SetUp() {
  }

  virtual ~ContentCheckerVaultTest(){
  }

  analyzer::checker::ContentCheckerVault contentCheckerVault;
};

TEST_F(ContentCheckerVaultTest, init)
{
  analyzer::checker::ContentCheckerVault vault;
  ASSERT_EQ(vault.GetNumCheckers(), 0);
}

TEST_F(ContentCheckerVaultTest, extraordinaryChecker)
{
  ASSERT_FALSE(contentCheckerVault.HasExtraordinaryChecker());
  contentCheckerVault.InitializeExtraordinaryChecker();
  ASSERT_TRUE(contentCheckerVault.HasExtraordinaryChecker());
}

TEST_F(ContentCheckerVaultTest, executableChecker)
{
  ASSERT_FALSE(contentCheckerVault.HasExecutableChecker());
  contentCheckerVault.InitializeExecutableChecker();
  ASSERT_TRUE(contentCheckerVault.HasExecutableChecker());
}

TEST_F(ContentCheckerVaultTest, externalLinkChecker)
{
  ASSERT_FALSE(contentCheckerVault.HasExternalLinkChecker());
  contentCheckerVault.InitializeExternalLinkChecker();
  ASSERT_TRUE(contentCheckerVault.HasExternalLinkChecker());
}

TEST_F(ContentCheckerVaultTest, macroChecker)
{
  ASSERT_FALSE(contentCheckerVault.HasMacroChecker());
  contentCheckerVault.InitializeMacroChecker();
  ASSERT_TRUE(contentCheckerVault.HasMacroChecker());
}
#endif