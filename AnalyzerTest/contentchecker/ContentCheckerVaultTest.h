/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef CONTENTCHECKERVAULTTEST_H
#define CONTENTCHECKERVAULTTEST_H

#include <gtest/gtest.h>

#include "AnalyzerLib/contentchecker/ContentCheckerVault.h"

class ContentCheckerVaultTest : public testing::Test
{
public:
  ContentCheckerVaultTest()
    : testing::Test()
  {
  }

  void SetUp() {
  }

  virtual ~ContentCheckerVaultTest(){
  }

};

TEST_F(ContentCheckerVaultTest, init)
{
  analyzer::checker::ContentCheckerVault vault;
  ASSERT_EQ(vault.GetNumCheckers(), 0);
}

#endif