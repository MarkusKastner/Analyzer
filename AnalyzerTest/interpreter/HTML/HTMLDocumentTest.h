/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef HTMLDOCUMENTTEST_H
#define HTMLDOCUMENTTEST_H

#include <gtest\gtest.h>

#include <string>

#include "AnalyzerLib\interpreter\HTML\Document.h"
#include "AnalyzerLib\interpreter\HTML\Heading.h"
#include "AnalyzerLib\interpreter\HTML\Paragraph.h"
#include "AnalyzerLib\interpreter\HTML\Table.h"

class HTMLDocumentTest : public testing::Test
{
public:
  HTMLDocumentTest() : 
    document()
  {}
  virtual ~HTMLDocumentTest() {}

  virtual void SetUp() {
  }

  analyzer::interpreter::HTML::Document document;
};

TEST_F(HTMLDocumentTest, getString)
{
  std::string emptyDocString("<!DOCTYPE html><html><head></head><body></body></html>");
  ASSERT_STREQ(document.GetString().c_str(), emptyDocString.c_str());
}

TEST_F(HTMLDocumentTest, setTitle)
{
  std::string pageTitleString("<!DOCTYPE html><html><head><title>Page Title</title></head><body></body></html>");
  document.SetTitle("Page Title");
  ASSERT_STREQ(document.GetString().c_str(), pageTitleString.c_str());
}

TEST_F(HTMLDocumentTest, addHeading)
{
  std::string headingString("<!DOCTYPE html><html><head></head><body><h1>Heading</h1></body></html>");
  document.AddHeading(analyzer::interpreter::HTML::Heading("Heading", 1));
  ASSERT_STREQ(document.GetString().c_str(), headingString.c_str());
}

TEST_F(HTMLDocumentTest, addParagraph)
{
  std::string paragraphString("<!DOCTYPE html><html><head></head><body><p>Paragraph</p></body></html>");
  document.AddParagraph(analyzer::interpreter::HTML::Paragraph("Paragraph"));
  ASSERT_STREQ(document.GetString().c_str(), paragraphString.c_str());
}

TEST_F(HTMLDocumentTest, addTable)
{
  std::string tableTestString("<!DOCTYPE html><html><head></head><body><table border=\"1\" cellpadding=\"1\" cellspacing=\"1\" style=\"width: 500px\"><thead><tr><th scope=\"col\">test</th><th scope=\"col\">test</th></tr></thead><tbody><tr><td>line1</td><td>line1</td></tr><tr><td>line2</td><td>line2</td></tr><tr><td>line3</td><td>line3</td></tr></tbody></table></body></html>");
  
  std::vector<std::string> header;
  header.push_back("test");
  header.push_back("test");

  std::vector<std::string> line1;
  line1.push_back("line1");
  line1.push_back("line1");

  std::vector<std::string> line2;
  line2.push_back("line2");
  line2.push_back("line2");

  std::vector<std::string> line3;
  line3.push_back("line3");
  line3.push_back("line3");

  analyzer::interpreter::HTML::Table table;
  table.SetHeader(header);
  table.AddLine(line1);
  table.AddLine(line2);
  table.AddLine(line3);

  document.AddTable(table);
  ASSERT_STREQ(document.GetString().c_str(), tableTestString.c_str());
}

TEST_F(HTMLDocumentTest, addLineFeed)
{
  std::string lfString("<!DOCTYPE html><html><head></head><body><p>Paragraph1</p><br><p>Paragraph2</p></body></html>");
  document.AddParagraph(analyzer::interpreter::HTML::Paragraph("Paragraph1"));
  document.AddLineFeed();
  document.AddParagraph(analyzer::interpreter::HTML::Paragraph("Paragraph2"));
  ASSERT_STREQ(document.GetString().c_str(), lfString.c_str());
}
#endif
