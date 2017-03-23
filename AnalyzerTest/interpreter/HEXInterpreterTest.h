/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef HEXINTERPRETERTEST_H
#define HEXINTERPRETERTEST_H

#include <gtest/gtest.h>

#include "AnalyzerLib/interpreter/HEXInterpreter.h"

class HEXInterpreterTest : public testing::Test
{
public:
  HEXInterpreterTest() 
    : data1(), data2()
  {}
  virtual ~HEXInterpreterTest() {}

  virtual void SetUp() {
    this->data1.reset(new std::vector<unsigned char>());
    this->data2.reset(new std::vector<unsigned char>());

    for (int i = 100; i < 110; i++) {
      this->data2->push_back(static_cast<unsigned char>(i));
    }

    for (int i = 0; i < 256; i++) {
      this->data1->push_back(static_cast<unsigned char>(i));
      this->data2->push_back(static_cast<unsigned char>(i));
    }

    for (int i = 200; i < 210; i++) {
      this->data2->push_back(static_cast<unsigned char>(i));
    }
  }

  std::shared_ptr<std::vector<unsigned char>> data1;
  std::shared_ptr<std::vector<unsigned char>> data2;
};

TEST_F(HEXInterpreterTest, init)
{
  analyzer::interpreter::HEXInterpreter interpreter;
  ASSERT_FALSE(interpreter.HasData());
  ASSERT_EQ(interpreter.GetFileFormat(), analyzer::core::FileFormat::hex);
}

TEST_F(HEXInterpreterTest, initWithData)
{
  analyzer::interpreter::HEXInterpreter interpreter(this->data1);
  ASSERT_TRUE(interpreter.HasData());
}

TEST_F(HEXInterpreterTest, getHex)
{
  analyzer::interpreter::HEXInterpreter interpreter(this->data1);
  std::vector<std::string> hex(interpreter.GetHexExpressions());
  ASSERT_STREQ(hex[0].c_str(), "00");
  ASSERT_STREQ(hex[255].c_str(), "ff");
}

TEST_F(HEXInterpreterTest, getHexAfterSetData)
{
  analyzer::interpreter::HEXInterpreter interpreter;
  interpreter.SetData(this->data1);
  std::vector<std::string> hex(interpreter.GetHexExpressions());
  ASSERT_STREQ(hex[0].c_str(), "00");
  ASSERT_STREQ(hex[255].c_str(), "ff");
}

TEST_F(HEXInterpreterTest, getHexWithLimits)
{
  analyzer::interpreter::HEXInterpreter interpreter;
  interpreter.SetData(this->data2, 10, 256);
  std::vector<std::string> hex(interpreter.GetHexExpressions());
  ASSERT_STREQ(hex[0].c_str(), "00");
  ASSERT_STREQ(hex[255].c_str(), "ff");
}

TEST_F(HEXInterpreterTest, getHexRows)
{
  analyzer::interpreter::HEXInterpreter interpreter;
  interpreter.SetData(this->data1);
  std::vector<std::vector<std::string>> hex(interpreter.GetHexRows());
  ASSERT_EQ(hex.size(), 16);
}
#endif