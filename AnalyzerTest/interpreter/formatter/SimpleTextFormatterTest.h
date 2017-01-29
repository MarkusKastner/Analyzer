/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef SIMPLETEXTFORMATTERTEST_H
#define SIMPLETEXTFORMATTERTEST_H

#include <gtest\gtest.h>

#include <memory>
#include <string>

#include "AnalyzerLib\interpreter\formatter\SimpleTextFormatter.h"

class SimpleTextFormatterTest : public testing::Test
{
public:
  SimpleTextFormatterTest()
    : data(new std::vector<unsigned char>({ 'a', 'b', 'c', 'd', 'e', '~' }))
  {}

  void SetUp(){
  }

  std::shared_ptr<std::vector<unsigned char>> data;
};

TEST_F(SimpleTextFormatterTest, formatSimpleText)
{
  analyzer::interpreter::SimpleTextFormatter formatter;
  formatter.SetData(data);
  ASSERT_STREQ(formatter.GetText()->c_str(), L"abcde~");
}

#endif