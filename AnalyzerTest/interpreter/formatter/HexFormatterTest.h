/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef HEXFORMATTERTEST_H
#define HEXFORMATTERTEST_H

#include <gtest\gtest.h>

#include <memory>
#include <string>

#include "AnalyzerLib\core\ByteCollection.h"
#include "AnalyzerLib\interpreter\formatter\HexFormatter.h"

class HexFormatterTest : public testing::Test
{
public:
  void SetUp() {
    char chars[] = { 255, 127, 42, 9, 13 , 32, 100, 199 };
    data.reset(new analyzer::core::ByteCollection(chars, 8));

    cmpStr = L"ff  7f  2a  9  d  20  64  c7    [ÿ][DEL][*][HT][CR][SPACE][d][Ç]";
  }

  std::shared_ptr<analyzer::core::ByteCollection> data;
  std::wstring cmpStr;
};

TEST_F(HexFormatterTest, formatHex)
{
  analyzer::interpreter::HexFormatter formatter;
  formatter.SetData(data);
  ASSERT_TRUE(formatter.GetText()->compare(cmpStr) == 0);
}

#endif