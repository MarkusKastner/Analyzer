#ifndef HTMLDOCUMENTTEST_H
#define HTMLDOCUMENTTEST_H

#include <gtest\gtest.h>

#include <string>

#include "AnalyzerLib\interpreter\HTML\Document.h"
#include "AnalyzerLib\interpreter\HTML\Heading.h"
#include "AnalyzerLib\interpreter\HTML\Paragraph.h"

class HTMLDocumentTest : public testing::Test
{
public:
  HTMLDocumentTest() : 
    document(), 
    emptyDocString(),
    pageTitleString(),
    headingString(),
    paragraphString()
  {}
  virtual ~HTMLDocumentTest() {}

  virtual void SetUp() {
    this->emptyDocString = "<!DOCTYPE html><html><head></head><body></body></html>";
    this->pageTitleString = "<!DOCTYPE html><html><head><title>Page Title</title></head><body></body></html>";
    this->headingString = "<!DOCTYPE html><html><head></head><body><h1>Heading</h1></body></html>";
    this->paragraphString = "<!DOCTYPE html><html><head></head><body><p>Paragraph</p></body></html>";
  }

  analyzer::interpreter::HTML::Document document;
  std::string emptyDocString;
  std::string pageTitleString;
  std::string headingString;
  std::string paragraphString;
};

TEST_F(HTMLDocumentTest, getString)
{
  ASSERT_STREQ(document.GetString().c_str(), this->emptyDocString.c_str());
}

TEST_F(HTMLDocumentTest, setTitle)
{
  document.SetTitle("Page Title");
  ASSERT_STREQ(document.GetString().c_str(), this->pageTitleString.c_str());
}

TEST_F(HTMLDocumentTest, addHeading)
{
  document.AddHeading(analyzer::interpreter::HTML::Heading("Heading", 1));
  ASSERT_STREQ(document.GetString().c_str(), this->headingString.c_str());
}

TEST_F(HTMLDocumentTest, addParagraph)
{
  document.AddParagraph(analyzer::interpreter::HTML::Paragraph("Paragraph"));
  ASSERT_STREQ(document.GetString().c_str(), this->paragraphString.c_str());
}
#endif
