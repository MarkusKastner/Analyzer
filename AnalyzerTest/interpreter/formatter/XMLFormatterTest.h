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
    xmlHeaderW(L"<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\" ?>")
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
};

TEST_F(XMLFormatterTest, xmlToken)
{
  formatter.SetData(createXMLData());
  auto token = formatter.GetXMLToken();

  ASSERT_EQ(token.size(), 6);
}

#endif