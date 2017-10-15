/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef JSICASECHECKERTEST_H
#define JSICASECHECKERTEST_H

#include <gtest/gtest.h>
#include "TestSupport.h"

#include "AnalyzerLib/contentchecker/javascript/JSICaseChecker.h"

class JSICaseCheckerTest : public testing::Test
{
public:
  JSICaseCheckerTest()
    : testing::Test()
  {
  }
};

TEST_F(JSICaseCheckerTest, data)
{
  std::shared_ptr<std::vector<unsigned char>> data(new std::vector<unsigned char>());
  data->push_back('x');

  analyzer::checker::JSICaseChecker jsICaseChecker(data);
  ASSERT_TRUE(jsICaseChecker.HasData());

  jsICaseChecker.ReleaseData();
  ASSERT_FALSE(jsICaseChecker.HasData());

  jsICaseChecker.SetData(data);
  ASSERT_TRUE(jsICaseChecker.HasData());

}

TEST_F(JSICaseCheckerTest, ifCase)
{
  auto jsIfSyntax(TestSupport::GetInstance()->GetDataFromTestFilesDir("JavascriptSyntax/if.txt"));
  size_t offset = 21;
  analyzer::checker::JSICaseChecker jsICaseChecker(jsIfSyntax);
  ASSERT_TRUE(jsICaseChecker.IsMyCase(offset));
}

#endif