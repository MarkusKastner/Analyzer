/* Copyright (C) 2016 - 2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef BITFORMATTERTEST_H
#define BITFORMATTERTEST_H

#include <gtest\gtest.h>

#include <memory>
#include <string>

#include "AnalyzerLib\core\ByteCollection.h"
#include "AnalyzerLib\interpreter\formatter\BitFormatter.h"

class BitFormatterTest : public testing::Test
{
public:
  void SetUp(){
    char chars[] = { 1, 2, 3, 4, 5 };
    data.reset(new analyzer::core::ByteCollection(chars, 5));
  }

  std::shared_ptr<analyzer::core::ByteCollection> data;
};

TEST_F(BitFormatterTest, formatBits)
{
  analyzer::interpreter::BitFormatter formatter;
  formatter.SetData(data);
  ASSERT_STREQ(formatter.GetText()->c_str(), L"00000001 00000010 00000011 00000100\n00000101");
}

#endif