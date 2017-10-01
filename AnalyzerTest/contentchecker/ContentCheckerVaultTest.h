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
  auto checker(contentCheckerVault.CreateExtraordinaryChecker());
  ASSERT_TRUE(static_cast<bool>(dynamic_cast<analyzer::checker::ExtraordinaryChecker*>(checker)));
}

TEST_F(ContentCheckerVaultTest, executableChecker)
{
  auto checker(contentCheckerVault.CreateExecutableChecker());
  ASSERT_TRUE(static_cast<bool>(dynamic_cast<analyzer::checker::ExecutableChecker*>(checker)));
}

TEST_F(ContentCheckerVaultTest, externalLinkChecker)
{
  auto checker(contentCheckerVault.CreateExternalLinkChecker());
  ASSERT_TRUE(static_cast<bool>(dynamic_cast<analyzer::checker::ExternalLinkChecker*>(checker)));
}

TEST_F(ContentCheckerVaultTest, macroChecker)
{
  auto checker(contentCheckerVault.CreateMacroChecker());
  ASSERT_TRUE(static_cast<bool>(dynamic_cast<analyzer::checker::MacroChecker*>(checker)));
}
#endif