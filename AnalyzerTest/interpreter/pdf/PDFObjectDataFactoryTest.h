/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef PDFOBJECTDATAFACTORYTEST_H
#define PDFOBJECTDATAFACTORYTEST_H

#include <vector>

#include <gtest\gtest.h>
#include "TestSupport.h"

#include "AnalyzerLib\interpreter\pdf\PDFObjectDataFactory.h"
#include "AnalyzerLib\interpreter\pdf\PDFTitleObjectData.h"

class PDFObjectDataFactoryTest : public testing::Test
{
public:
  PDFObjectDataFactoryTest()
  :testing::Test(), data1()
  {}
  virtual ~PDFObjectDataFactoryTest() {}

  virtual void SetUp() {
    this->data1 = TestSupport::GetInstance()->GetDataFromTestFilesDir("test.pdf");
  }
  std::shared_ptr<std::vector<unsigned char>> data1;
};

TEST_F(PDFObjectDataFactoryTest, emptyData)
{
  std::shared_ptr<std::vector<unsigned char>> data;

  ASSERT_FALSE(analyzer::interpreter::PDFObjectDataFactory::CreatePDFObjectData(data, 0, 100));
}

TEST_F(PDFObjectDataFactoryTest, PDFTitleObjectData)
{
  std::unique_ptr<analyzer::interpreter::PDFObjectData> objData = std::move(analyzer::interpreter::PDFObjectDataFactory::CreatePDFObjectData(this->data1, 16, 24));
  bool isobj = dynamic_cast<analyzer::interpreter::PDFTitleObjectData*>(objData.get());
  ASSERT_TRUE(isobj);
}
#endif