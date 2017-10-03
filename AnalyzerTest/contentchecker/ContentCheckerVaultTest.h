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
    : testing::Test(), contentCheckerVault(), dummyData1(new std::vector<unsigned char>())
  {
  }

  void SetUp() {
    for (unsigned char i = 65; i < 127; ++i) {
      this->dummyData1->push_back(i);
    }
    this->contentCheckerVault.SetCurrentData(this->dummyData1);
  }

  virtual ~ContentCheckerVaultTest(){
  }

  analyzer::checker::ContentCheckerVault contentCheckerVault;
  std::shared_ptr<std::vector<unsigned char>> dummyData1;
};

TEST_F(ContentCheckerVaultTest, init)
{
  analyzer::checker::ContentCheckerVault vault;
  ASSERT_EQ(vault.GetNumCheckers(), 0);
}

TEST_F(ContentCheckerVaultTest, extraordinaryChecker)
{
  ASSERT_FALSE(this->contentCheckerVault.HasExtraordinaryChecker());
  this->contentCheckerVault.InitializeExtraordinaryChecker();
  ASSERT_TRUE(this->contentCheckerVault.HasExtraordinaryChecker());
}

TEST_F(ContentCheckerVaultTest, executableChecker)
{
  ASSERT_FALSE(this->contentCheckerVault.HasExecutableChecker());
  this->contentCheckerVault.InitializeExecutableChecker();
  ASSERT_TRUE(this->contentCheckerVault.HasExecutableChecker());
}

TEST_F(ContentCheckerVaultTest, externalLinkChecker)
{
  ASSERT_FALSE(this->contentCheckerVault.HasExternalLinkChecker());
  this->contentCheckerVault.InitializeExternalLinkChecker();
  ASSERT_TRUE(this->contentCheckerVault.HasExternalLinkChecker());
}

TEST_F(ContentCheckerVaultTest, macroChecker)
{
  ASSERT_FALSE(this->contentCheckerVault.HasMacroChecker());
  this->contentCheckerVault.InitializeMacroChecker();
  ASSERT_TRUE(this->contentCheckerVault.HasMacroChecker());
}
#endif