/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef XMLFORMATTERTEST_H
#define XMLFORMATTERTEST_H

#include <gtest\gtest.h>

#include <memory>
#include <string>

#include "AnalyzerLib\core\ByteCollection.h"
#include "AnalyzerLib\interpreter\formatter\XMLFormatter.h"

class XMLFormatterTest : public testing::Test
{
public:
  XMLFormatterTest()
    : formatter(), 
    xmlHeaderB("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\" ?>"),
    xmlHeaderW(L"<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\" ?>"),
    cmpStrg1(L"<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\" ?>\n<tag1>\n  <tag2>some text</tag2>\n</tag1>")
  {

  }

  std::shared_ptr<analyzer::core::ByteCollection> createXMLData()
  {
    std::string fileData(this->xmlHeaderB);
    fileData += "<tag1><tag2>some text</tag2></tag1>";
    std::shared_ptr<analyzer::core::ByteCollection> data(new analyzer::core::ByteCollection(fileData.c_str(), fileData.size()));
    return data;
  }

  analyzer::interpreter::XMLFormatter formatter;
  std::string xmlHeaderB;
  std::wstring xmlHeaderW;
  std::wstring cmpStrg1;
};

TEST_F(XMLFormatterTest, getFormatedText)
{
  formatter.SetData(createXMLData());
  ASSERT_STREQ(formatter.GetText()->c_str(), this->cmpStrg1.c_str());
}

#endif