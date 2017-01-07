#ifndef SIMPLETEXTFORMATTERTEST_H
#define SIMPLETEXTFORMATTERTEST_H

#include <gtest\gtest.h>

#include <memory>
#include <string>

#include "AnalyzerLib\core\ByteCollection.h"
#include "AnalyzerLib\interpreter\formatter\SimpleTextFormatter.h"

class SimpleTextFormatterTest : public testing::Test
{
public:
  void SetUp(){
    char chars[] = { 'a', 'b', 'c', 'd', 'e', '~' };
    data.reset(new analyzer::core::ByteCollection(chars, 6));
  }

  std::shared_ptr<analyzer::core::ByteCollection> data;
};

TEST_F(SimpleTextFormatterTest, formatSimpleText)
{
  analyzer::interpreter::SimpleTextFormatter formatter;
  formatter.SetData(data);
  ASSERT_STREQ(formatter.GetText().c_str(), L"abcde~");
}

#endif