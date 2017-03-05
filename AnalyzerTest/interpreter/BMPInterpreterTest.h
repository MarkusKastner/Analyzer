/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef BMPINTERPRETERTEST_H
#define BMPINTERPRETERTEST_H

#include <gtest\gtest.h>

#include <memory>
#include <vector>

#include "TestSupport.h"

#include "AnalyzerLib\interpreter\BMPInterpreter.h"

class BMPInterpreterTest : public testing::Test
{
public:
  BMPInterpreterTest()
    : interpreter(),
      path_16_1(),
      path_16_2(),
      path_24(),
      path_32()
  {}
  virtual ~BMPInterpreterTest() {}

  void SetUp() {
    std::string testDir("bmp/");

    this->path_16_1 = testDir + "test16_1.bmp";
    this->path_16_2 = testDir + "test16_2.bmp";
    this->path_24 = testDir + "test24.bmp";
    this->path_32 = testDir + "test32.bmp";
  }

  analyzer::interpreter::BMPInterpreter interpreter;
  std::string path_16_1;
  std::string path_16_2;
  std::string path_24;
  std::string path_32;
};

TEST_F(BMPInterpreterTest, open16_1)
{
  std::shared_ptr<std::vector<unsigned char>> data(TestSupport::GetInstance()->GetDataFromTestFilesDir(this->path_16_1));
  this->interpreter.SetData(data);
  ASSERT_STREQ(this->interpreter.GetFileHeader().Type.c_str(), "BM");
  ASSERT_EQ(this->interpreter.GetInfoHeader().Width, 40);
}

TEST_F(BMPInterpreterTest, richText)
{
  ASSERT_TRUE(this->interpreter.UseRichText());
}

TEST_F(BMPInterpreterTest, getText)
{
  std::string text(this->interpreter.GetText());
  std::string compText("<!DOCTYPE html><html><head><title>Windows Bitmap</title></head><body></body></html>");
  ASSERT_STREQ(text.c_str(), compText.c_str());
}

#endif