#ifndef TEXTGLYPHTEST_H
#define TEXTGLYPHTEST_H

#include <gtest/gtest.h>

#include <string>
#include <memory>
#include <vector>

#include "AnalyzerLib\interpreter\TextGlyph.h"
#include "AnalyzerLib\core\ByteCollection.h"
#include "AnalyzerLib\core\Byte.h"

class TextGlyphTest : public testing::Test
{
public:
  TextGlyphTest()
    : data(), numBytes(1)
  {}
  ~TextGlyphTest(){}

  void SetUp(){
    data.push_back(std::shared_ptr<analyzer::core::Byte>(new analyzer::core::Byte('0')));
  }
  std::vector<std::shared_ptr<analyzer::core::Byte>> data;
  size_t numBytes;
};

TEST_F(TextGlyphTest, init)
{
  analyzer::interpreter::TextGlyph textGlyph;
  ASSERT_FALSE(textGlyph.HasExpression());
}

TEST_F(TextGlyphTest, compare)
{
  analyzer::interpreter::TextGlyph textGlyph1;
  analyzer::interpreter::TextGlyph textGlyph2;
  ASSERT_TRUE(textGlyph1 == textGlyph2);
}

TEST_F(TextGlyphTest, initValue)
{
  analyzer::interpreter::TextGlyph textGlyph(data);
  ASSERT_EQ(textGlyph.NumBytes(), numBytes);
}

TEST_F(TextGlyphTest, GetDefaultPlainText)
{
  analyzer::interpreter::TextGlyph textGlyph(data);
  ASSERT_STREQ(textGlyph.GetPlainText().c_str(), std::string("0").c_str());
}

#endif