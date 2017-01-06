#ifndef FORMATTERTEST_H
#define FORMATTERTEST_H

#include <gtest\gtest.h>

#include <memory>
#include <string>

#include "AnalyzerLib\core\ByteCollection.h"
#include "AnalyzerLib\interpreter\formatter\Formatter.h"

class FormatterTest : public testing::Test
{
public:
  class SomeFormatter : public analyzer::interpreter::Formatter
  {
  public:
    SomeFormatter()
      :analyzer::interpreter::Formatter()
    {}
    virtual ~SomeFormatter(){}

    virtual std::wstring GetText(){ 
      std::string text;
      auto data = this->getData();
      for (auto& byte : (*data)){
        text.push_back(static_cast<char>(byte->GetValue()));
      }
      return std::wstring(text.begin(), text.end()); 
    }
  };

};

TEST_F(FormatterTest, init)
{
  char chars[] = { 'a', 'b', 'c', 'd', 'e' };
  std::shared_ptr<analyzer::core::ByteCollection> data(new analyzer::core::ByteCollection(chars, 5));
  SomeFormatter formatter;
  formatter.SetData(data);
  ASSERT_STREQ(formatter.GetText().c_str(), L"abcde");
}

#endif