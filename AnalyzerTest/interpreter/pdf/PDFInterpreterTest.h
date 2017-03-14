/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef PDFINTERPRETERTEST_H
#define PDFINTERPRETERTEST_H

#include <gtest/gtest.h>
#include "AnalyzerLib/interpreter/pdf/PDFInterpreter.h"
#include "AnalyzerLib/interpreter/pdf/PDFObject.h"

#include <string>
#include <memory>
#include <vector>

#include "TestSupport.h"

class PDFInterpreterTest : public testing::Test
{
public:
  PDFInterpreterTest()
    :data(),
    dataObj1(19,24),
    dataObj2(63,37),
    dataObj3(120,157),
    dataObj4(297,93),
    dataObj5(410,55),
    dataObj6(485, 82)
  {}
  virtual ~PDFInterpreterTest() {}

  void SetUp() {
    this->data = TestSupport::GetInstance()->GetDataFromTestFilesDir("test.pdf");
  }

  std::shared_ptr<std::vector<unsigned char>> data;
  const std::pair<size_t, size_t> dataObj1;
  const std::pair<size_t, size_t> dataObj2;
  const std::pair<size_t, size_t> dataObj3;
  const std::pair<size_t, size_t> dataObj4;
  const std::pair<size_t, size_t> dataObj5;
  const std::pair<size_t, size_t> dataObj6;
};

TEST_F(PDFInterpreterTest, init)
{
  analyzer::interpreter::PDFInterpreter interpreter;
  ASSERT_FALSE(interpreter.HasData());
}

TEST_F(PDFInterpreterTest, initWithData)
{
  analyzer::interpreter::PDFInterpreter interpreter(data);
  ASSERT_TRUE(interpreter.HasData());
}

TEST_F(PDFInterpreterTest, setData)
{
  analyzer::interpreter::PDFInterpreter interpreter;
  interpreter.SetData(data);
  ASSERT_TRUE(interpreter.HasData());
}

TEST_F(PDFInterpreterTest, initObject)
{
  analyzer::interpreter::PDFObject obj(1, 0);
  ASSERT_EQ(obj.GetNumber(), 1);
  ASSERT_EQ(obj.GetRevision(), 0);
}

TEST_F(PDFInterpreterTest, setObjectNumber)
{
  analyzer::interpreter::PDFObject obj;
  obj.SetNumber(1, 0);
  ASSERT_EQ(obj.GetNumber(), 1);
  ASSERT_EQ(obj.GetRevision(), 0);
}

TEST_F(PDFInterpreterTest, addObject)
{
  analyzer::interpreter::PDFInterpreter interpreter;
  analyzer::interpreter::PDFObject obj(1, 0);
  interpreter.AddPDFObject(obj);
  ASSERT_EQ(interpreter.GetPDFObject(1, 0).GetNumber(), 1);
}

TEST_F(PDFInterpreterTest, setObjectData)
{
  analyzer::interpreter::PDFObject obj(1, 0);
  obj.SetData(this->data, this->dataObj1.first, this->dataObj1.second);
  ASSERT_EQ(obj.GetDataOffset(), 19);
  ASSERT_EQ(obj.GetObjectOffset(), 24);
}

TEST_F(PDFInterpreterTest, getRichTextExpression)
{
  std::string compString("<h3>+ Object 1 0</h3>");
  analyzer::interpreter::PDFObject obj(1, 0);
  obj.SetData(this->data, this->dataObj1.first, this->dataObj1.second);
  ASSERT_STREQ(obj.GetRichTextExpression().c_str(), compString.c_str());
}

TEST_F(PDFInterpreterTest, internalCreateObjects)
{
  std::string compString("<h3>+ Object 1 0</h3>");
  analyzer::interpreter::PDFInterpreter interpreter(this->data);
  ASSERT_STREQ(interpreter.GetPDFObject(1, 0).GetRichTextExpression().c_str(), compString.c_str());
}

TEST_F(PDFInterpreterTest, foldBlock)
{
  std::string compStringOpen("<h3>- Object 1 0</h3><p>&lt;&lt; /Title (Hallo Welt) &gt;&gt;</p>");
  std::string compStringFolded("<h3>+ Object 1 0</h3>");
  analyzer::interpreter::PDFObject obj(1, 0);
  obj.SetData(this->data, this->dataObj1.first, this->dataObj1.second);
  
  obj.Unfold();
  ASSERT_STREQ(obj.GetRichTextExpression().c_str(), compStringOpen.c_str());

  obj.Fold();
  ASSERT_STREQ(obj.GetRichTextExpression().c_str(), compStringFolded.c_str());
}

TEST_F(PDFInterpreterTest, switchFolding)
{
  std::string compStringOpen("<h3>- Object 1 0</h3><p>&lt;&lt; /Title (Hallo Welt) &gt;&gt;</p>");
  std::string compStringFolded("<h3>+ Object 1 0</h3>");
  analyzer::interpreter::PDFInterpreter interpreter(this->data);

  ASSERT_STREQ(interpreter.GetPDFObject(1, 0).GetRichTextExpression().c_str(), compStringFolded.c_str());
  interpreter.SwitchFolding("Object 1 0");
  ASSERT_STREQ(interpreter.GetPDFObject(1, 0).GetRichTextExpression().c_str(), compStringOpen.c_str());
  interpreter.SwitchFolding("Object 1 0");
  ASSERT_STREQ(interpreter.GetPDFObject(1, 0).GetRichTextExpression().c_str(), compStringFolded.c_str());
}

TEST_F(PDFInterpreterTest, ObjectData2StringObj1)
{
  std::string compString("&lt;&lt; /Title (Hallo Welt) &gt;&gt;");
  analyzer::interpreter::PDFObject obj(1, 0);
  obj.SetData(this->data, this->dataObj1.first, this->dataObj1.second);

  ASSERT_STREQ(obj.ObjectData2String().c_str(), compString.c_str());
}

#endif