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
#include "AnalyzerLib/core/File.h"
#include "AnalyzerLib/interpreter/BMPInterpreter.h"

#include <string>
#include <memory>
#include <vector>

#include "TestSupport.h"

class PDFInterpreterTest : public testing::Test
{
public:
  class SomeObserver : public analyzer::interpreter::InterpreterObserver
  {
  public:
    SomeObserver() : file(){}
    virtual ~SomeObserver() {}

    virtual void AddInternalFile(const std::shared_ptr<analyzer::core::File> & internalFile) {
      this->file = internalFile;
    }

    const std::shared_ptr<analyzer::core::File> & GetFile() const { return this->file; }

  private:
    std::shared_ptr<analyzer::core::File> file;
  };

  PDFInterpreterTest()
    :data(),
    dataWithStream(new std::vector<unsigned char>()),
    dummyFileWithStream(new std::vector<unsigned char>()),
    dataObj1(19,24),
    dataObj2(63,37),
    dataObj3(120,157),
    dataObj4(297,93),
    dataObj5(410,55),
    dataObj6(485, 82),
    interpreterObserver()
  {}
  virtual ~PDFInterpreterTest() {}

  void SetUp() {
    this->data = TestSupport::GetInstance()->GetDataFromTestFilesDir("test.pdf");

    auto bmp = TestSupport::GetInstance()->GetDataFromTestFilesDir("bmp/test16_1.bmp");

    std::string streamDataStrgBeg("<</Length 3338/Filter /FlateDecode>>stream");
    std::string streamDataStrgEnd("endstream endobj");
    this->dataWithStream->assign(streamDataStrgBeg.begin(), streamDataStrgBeg.end());
    this->dataWithStream->insert(this->dataWithStream->end(), bmp->begin(), bmp->end());
    this->dataWithStream->insert(this->dataWithStream->end(), streamDataStrgEnd.begin(), streamDataStrgEnd.end());

    std::string dummyFileBeginStr("%PDF-1.4\n1 0 obj ");
    std::string dummyFileEndStr("\nxref\n0 2\n0000000000 65535 f\n0000000009 00000 n\ntrailer\n<< /Size 2\n>>\nstartxref\n534\n%%EOF");
    this->dummyFileWithStream->assign(dummyFileBeginStr.begin(), dummyFileBeginStr.end());
    this->dummyFileWithStream->insert(this->dummyFileWithStream->end(), this->dataWithStream->begin(), this->dataWithStream->end());
    this->dummyFileWithStream->insert(this->dummyFileWithStream->end(), dummyFileEndStr.begin(), dummyFileEndStr.end());
  }

  std::shared_ptr<std::vector<unsigned char>> data;
  std::shared_ptr<std::vector<unsigned char>> dataWithStream;
  std::shared_ptr<std::vector<unsigned char>> dummyFileWithStream;
  const std::pair<size_t, size_t> dataObj1;
  const std::pair<size_t, size_t> dataObj2;
  const std::pair<size_t, size_t> dataObj3;
  const std::pair<size_t, size_t> dataObj4;
  const std::pair<size_t, size_t> dataObj5;
  const std::pair<size_t, size_t> dataObj6;
  SomeObserver interpreterObserver;
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

TEST_F(PDFInterpreterTest, CreateObjects)
{
  std::string compString("<h3>+ Object 1 0</h3>");
  analyzer::interpreter::PDFInterpreter interpreter(this->data);
  interpreter.CreateObjects();
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
  interpreter.CreateObjects();

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

TEST_F(PDFInterpreterTest, hasStream)
{
  analyzer::interpreter::PDFObject obj(1, 0);
  obj.SetData(this->dataWithStream, 0, this->dataWithStream->size() - 1);
  ASSERT_TRUE(obj.HasStreamObj());
}

TEST_F(PDFInterpreterTest, findStreamLimits)
{
  analyzer::interpreter::PDFObject obj(1, 0);
  obj.SetData(this->dataWithStream, 0, this->dataWithStream->size() - 1);
  size_t streamStartIndex = obj.FindStreamStartIndex();
  ASSERT_EQ(streamStartIndex, 42);
  ASSERT_EQ(obj.FindStreamOffset(streamStartIndex), 3338);
}

TEST_F(PDFInterpreterTest, addInternalFile)
{
  analyzer::interpreter::PDFInterpreter interpreter(this->dummyFileWithStream);
  interpreter.SetObserver(&this->interpreterObserver);
  interpreter.CreateObjects();
  ASSERT_STREQ(this->interpreterObserver.GetFile()->GetFileName().c_str(), "Object 1-0");
  bool isBMP = false;
  if (dynamic_cast<analyzer::interpreter::BMPInterpreter*>(this->interpreterObserver.GetFile()->GetInterpreter().get())) {
    isBMP = true;
  }
  ASSERT_TRUE(isBMP);
}
#endif