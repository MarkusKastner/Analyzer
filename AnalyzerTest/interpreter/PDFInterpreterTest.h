/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef PDFINTERPRETERTEST_H
#define PDFINTERPRETERTEST_H

#include <gtest\gtest.h>
#include "AnalyzerLib\interpreter\PDFInterpreter.h"

#include <string>
#include <memory>
#include <vector>

#include "TestSupport.h"

class PDFInterpreterTest : public testing::Test
{
public:
  PDFInterpreterTest()
    :text()
  {}
  virtual ~PDFInterpreterTest() {}

  void SetUp() {
    this->text = TestSupport::GetInstance()->GetDataFromTestFilesDir("test.pdf");
  }

  std::shared_ptr<std::vector<unsigned char>> text;
};

TEST_F(PDFInterpreterTest, init)
{
  analyzer::interpreter::PDFInterpreter interpreter;
  ASSERT_FALSE(interpreter.HasData());
}

TEST_F(PDFInterpreterTest, initWithData)
{
  analyzer::interpreter::PDFInterpreter interpreter(text);
  ASSERT_TRUE(interpreter.HasData());
}

TEST_F(PDFInterpreterTest, setData)
{
  analyzer::interpreter::PDFInterpreter interpreter;
  interpreter.SetData(text);
  ASSERT_TRUE(interpreter.HasData());
}

#endif