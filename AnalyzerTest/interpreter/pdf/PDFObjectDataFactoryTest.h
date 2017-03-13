/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef PDFOBJECTDATAFACTORYTEST_H
#define PDFOBJECTDATAFACTORYTEST_H

#include <vector>

#include <gtest\gtest.h>
#include "AnalyzerLib\interpreter\pdf\PDFObjectDataFactory.h"

class PDFObjectDataFactoryTest : public testing::Test
{
public:

  std::shared_ptr<std::vector<unsigned char>> data1;
};

TEST_F(PDFObjectDataFactoryTest, emptyData)
{
  std::shared_ptr<std::vector<unsigned char>> data;

  ASSERT_FALSE(analyzer::interpreter::PDFObjectDataFactory::CreatePDFObjectData(data, 0, 100));
}

#endif