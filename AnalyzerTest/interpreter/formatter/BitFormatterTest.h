/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef BITFORMATTERTEST_H
#define BITFORMATTERTEST_H

#include <gtest\gtest.h>

#include <memory>
#include <string>

#include "AnalyzerLib\interpreter\formatter\BitFormatter.h"

class BitFormatterTest : public testing::Test
{
public:
  BitFormatterTest()
    :data(new std::vector<unsigned char>({ 1, 2, 3, 4, 5 }))
  {}
  void SetUp(){

    cmpStr = L"00000001  00000010  00000011  00000100    [001][002][003][004]\n";
    cmpStr += L"00000101                                  [005]";
  }

  std::shared_ptr<std::vector<unsigned char>> data;
  std::wstring cmpStr;
};

TEST_F(BitFormatterTest, formatBits)
{
  analyzer::interpreter::BitFormatter formatter;
  formatter.SetData(data);
  ASSERT_STREQ(formatter.GetText()->c_str(), cmpStr.c_str());
}

#endif