/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef XMLINTERPRETERTEST_H
#define XMLINTERPRETERTEST_H

#include <gtest\gtest.h>
#include "AnalyzerLib\interpreter\XMLInterpreter.h"

#include <string>
#include <memory>
#include <vector>

class XMLInterpreterTest : public testing::Test
{
public:
  XMLInterpreterTest() : 
    data1(), data2(), data2begin(9), data2Offset(98),
    xmlHeader("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\" ?>"),
    cmpStrg1()
  {}

  virtual ~XMLInterpreterTest() {}

  void SetUp() {
    this->data1 = this->createXMLData1();
    this->data2 = this->createXMLData2();
  }

  std::shared_ptr<std::vector<unsigned char>> data1;
  std::shared_ptr<std::vector<unsigned char>> data2;
  size_t data2begin;
  size_t data2Offset;
  std::string xmlHeader;
  std::string cmpStrg1;
  
  std::shared_ptr<std::vector<unsigned char>> createXMLData1();
  std::shared_ptr<std::vector<unsigned char>> createXMLData2();
};

TEST_F(XMLInterpreterTest, init)
{
  analyzer::interpreter::XMLInterpreter interpreter;
  ASSERT_FALSE(interpreter.HasData());
}

TEST_F(XMLInterpreterTest, initWithData)
{
  analyzer::interpreter::XMLInterpreter interpreter(this->data1);
  ASSERT_TRUE(interpreter.HasData());
}

TEST_F(XMLInterpreterTest, limits)
{
  analyzer::interpreter::XMLInterpreter interpreter(this->data2, this->data2begin, this->data2Offset);
  ASSERT_STREQ(interpreter.GetText().c_str(), this->cmpStrg1.c_str());
}

std::shared_ptr<std::vector<unsigned char>> XMLInterpreterTest::createXMLData1()
{
  this->cmpStrg1 = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\" ?>\n<tag1>\n  <tag2>some text</tag2>\n  <tag3/>\n</tag1>";
  std::string fileData(this->xmlHeader);
  fileData += "<tag1><tag2>some text</tag2><tag3/></tag1>";
  std::shared_ptr<std::vector<unsigned char>> data(new std::vector<unsigned char>(fileData.begin(), fileData.end()));
  return data;
}

std::shared_ptr<std::vector<unsigned char>> XMLInterpreterTest::createXMLData2()
{
  this->cmpStrg1 = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\" ?>\n<tag1>\n  <tag2>some text</tag2>\n  <tag3/>\n</tag1>";

  std::string fileData("some data");
  fileData += this->xmlHeader;
  fileData += "<tag1><tag2>some text</tag2><tag3/></tag1>";
  fileData += "some other data";
  std::shared_ptr<std::vector<unsigned char>> data(new std::vector<unsigned char>(fileData.begin(), fileData.end()));
  return data;
}
#endif