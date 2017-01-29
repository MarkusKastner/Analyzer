/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef FORMATTERTEST_H
#define FORMATTERTEST_H

#include <gtest\gtest.h>

#include <memory>
#include <string>

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

    SomeFormatter(const std::shared_ptr<std::vector<unsigned char>> & data)
      :analyzer::interpreter::Formatter(data)
    {}

    virtual ~SomeFormatter(){}

    virtual std::shared_ptr<std::wstring> GetText(){
      std::string text;
      auto data = this->getData();
      for (auto& byte : (*data)){
        text.push_back(static_cast<char>(byte));
      }
      return std::shared_ptr<std::wstring>(new std::wstring(text.begin(), text.end()));
    }
  };

};

TEST_F(FormatterTest, init)
{
  std::shared_ptr<std::vector<unsigned char>> data (new std::vector<unsigned char>({ 'a', 'b', 'c', 'd', 'e' }));
  SomeFormatter formatter;
  formatter.SetData(data);
  ASSERT_STREQ(formatter.GetText().get()->c_str(), L"abcde");
}

TEST_F(FormatterTest, initWithData)
{
  std::shared_ptr<std::vector<unsigned char>> data(new std::vector<unsigned char>({ 'a', 'b', 'c', 'd', 'e' }));
  SomeFormatter formatter(data);
  ASSERT_STREQ(formatter.GetText().get()->c_str(), L"abcde");
}

TEST_F(FormatterTest, functionalHighlightingExp)
{
  SomeFormatter formatter;
  formatter.AddFunctionalHighlightingExp(L"<test");
  ASSERT_STREQ(formatter.GetFunctionalHighlightingExp()[0].c_str(), L"<test");
}

#endif