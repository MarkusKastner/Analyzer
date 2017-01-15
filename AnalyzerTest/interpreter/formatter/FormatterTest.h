/* Copyright (C) 2016 - 2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

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

    virtual std::shared_ptr<std::wstring> GetText(){
      std::string text;
      auto data = this->getData();
      for (auto& byte : (*data)){
        text.push_back(static_cast<char>(byte->GetValue()));
      }
      return std::shared_ptr<std::wstring>(new std::wstring(text.begin(), text.end()));
    }
  };

};

TEST_F(FormatterTest, init)
{
  char chars[] = { 'a', 'b', 'c', 'd', 'e' };
  std::shared_ptr<analyzer::core::ByteCollection> data(new analyzer::core::ByteCollection(chars, 5));
  SomeFormatter formatter;
  formatter.SetData(data);
  ASSERT_STREQ(formatter.GetText().get()->c_str(), L"abcde");
}

TEST_F(FormatterTest, functionalHighlightingExp)
{
  SomeFormatter formatter;
  formatter.AddFunctionalHighlightingExp(L"<test");
  ASSERT_STREQ(formatter.GetFunctionalHighlightingExp()[0].c_str(), L"<test");
}

#endif