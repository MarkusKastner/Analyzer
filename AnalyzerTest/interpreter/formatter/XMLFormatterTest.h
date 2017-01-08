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

TEST_F(XMLFormatterTest, xmlToken)
{
  formatter.SetData(createXMLData());
  auto token = formatter.GetXMLToken();

  ASSERT_EQ(token.size(), 6);
}

TEST_F(XMLFormatterTest, getHeaderAsInlineToken)
{
  auto token = formatter.CreateToken(L"<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\" ?>");
  ASSERT_EQ(token.GetTokenType(), analyzer::interpreter::XMLFormatter::XMLToken::Inline);
}

TEST_F(XMLFormatterTest, getOpenToken)
{
  auto token = formatter.CreateToken(L"<open>");
  ASSERT_EQ(token.GetTokenType(), analyzer::interpreter::XMLFormatter::XMLToken::Open);
}

TEST_F(XMLFormatterTest, getCloseToken)
{
  auto token = formatter.CreateToken(L"</close>");
  ASSERT_EQ(token.GetTokenType(), analyzer::interpreter::XMLFormatter::XMLToken::Close);
}

TEST_F(XMLFormatterTest, getInlineToken)
{
  auto token = formatter.CreateToken(L"<inline someAttr=\"0\"/>");
  ASSERT_EQ(token.GetTokenType(), analyzer::interpreter::XMLFormatter::XMLToken::Inline);
}

TEST_F(XMLFormatterTest, getCommentToken)
{
  auto token = formatter.CreateToken(L"<!--<inline someAttr=\"0\"/>-->");
  ASSERT_EQ(token.GetTokenType(), analyzer::interpreter::XMLFormatter::XMLToken::Comment);
}

TEST_F(XMLFormatterTest, getFormatedText)
{
  formatter.SetData(createXMLData());
  ASSERT_STREQ(formatter.GetText().c_str(), this->cmpStrg1.c_str());
}

TEST_F(XMLFormatterTest, getOpenHighlightTags)
{
  formatter.SetData(createXMLData());
  auto hlTags = formatter.GetOpenHLTags();
  ASSERT_STREQ(hlTags[0].c_str(), L"<?xml");
  ASSERT_STREQ(hlTags[1].c_str(), L"<tag1");
  ASSERT_STREQ(hlTags[2].c_str(), L"<tag2");
}

TEST_F(XMLFormatterTest, getClosingHighlightTags)
{
  formatter.SetData(createXMLData());
  auto hlTags = formatter.GetClosingHLTags();
  ASSERT_STREQ(hlTags[0].c_str(), L"</tag2>");
  ASSERT_STREQ(hlTags[1].c_str(), L"</tag1>");
}

#endif