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

#include "AnalyzerLib\interpreter\formatter\XMLFormatter.h"

class XMLFormatterTest : public testing::Test
{
public:
  XMLFormatterTest()
    : formatter(), 
    xmlHeaderB("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\" ?>"),
    xmlHeaderW(L"<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\" ?>"),
    cmpStrg1(),
    cmpStrg2()
  {

  }

  std::shared_ptr<std::vector<unsigned char>> createXMLData1()
  {
    cmpStrg1 = L"<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\" ?>\n<tag1>\n  <tag2>some text</tag2>\n  <tag3/>\n</tag1>";
    std::string fileData(this->xmlHeaderB);
    fileData += "<tag1><tag2>some text</tag2><tag3/></tag1>";
    std::shared_ptr<std::vector<unsigned char>> data(new std::vector<unsigned char>(fileData.begin(), fileData.end()));
    return data;
  }

  std::shared_ptr<std::vector<unsigned char>> createXMLData2()
  {
    cmpStrg2 = L"<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\" ?>\n<tag1>\n  <tag4/>\n  <tag2>some text</tag2>\n  <tag3/>\n</tag1>";
    std::string fileData(this->xmlHeaderB);
    fileData += "<tag1><tag4/><tag2>some text</tag2><tag3/></tag1>";
    std::shared_ptr<std::vector<unsigned char>> data(new std::vector<unsigned char>(fileData.begin(), fileData.end()));
    return data;
  }

  analyzer::interpreter::XMLFormatter formatter;
  std::string xmlHeaderB;
  std::wstring xmlHeaderW;
  std::wstring cmpStrg1;
  std::wstring cmpStrg2;
};

TEST_F(XMLFormatterTest, getFormatedText1)
{
  formatter.SetData(createXMLData1());
  ASSERT_STREQ(formatter.GetText()->c_str(), this->cmpStrg1.c_str());
}

TEST_F(XMLFormatterTest, getFormatedText2)
{
  formatter.SetData(createXMLData2());
  ASSERT_STREQ(formatter.GetText()->c_str(), this->cmpStrg2.c_str());
}

#endif