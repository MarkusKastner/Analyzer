/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef ANALYZINGSTRATEGYTEST_H
#define ANALYZINGSTRATEGYTEST_H

#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <vector>

#include "AnalyzerLib\strategy\AnalyzingStrategy.h"
#include "AnalyzerLib\strategy\Result.h"
#include "AnalyzerLib\definitions\Definition.h"
#include "AnalyzerLib\definitions\DefinitionSource.h"

std::shared_ptr<std::vector<unsigned char>> createData();
std::vector<std::wstring> findTags(const std::wstring & text);

class AnalyzingStrategyTest : public testing::Test
{
public:
  class TextResult : public analyzer::strategy::Result
  {
  public:
    TextResult(const analyzer::strategy::Result::Classification & classification, const std::wstring & expression)
      :analyzer::strategy::Result(classification), expression(expression)
    {
    }
    virtual ~TextResult(){}
    const std::wstring & GetExpression() { return this->expression; }

  private:
    std::wstring expression;
  };

  class TestDef : public analyzer::definition::Definition
  {
  public:
    TestDef(const unsigned int & id, const std::wstring & expression)
      : analyzer::definition::Definition(id), expression(expression)
    {}

    virtual ~TestDef(){}

    void SetExpression(const std::wstring & expression) { this->expression = expression; }
    const std::wstring & GetExpression() const { return this->expression; }

  private:
    std::wstring expression;
  };

  class TestSource : public analyzer::definition::DefinitionSource
  {
  public:
    TestSource()
      : analyzer::definition::DefinitionSource()
    {
      this->setName("test_defs");
    }

    virtual ~TestSource(){}
  };

  class SomeAnalyzingStrategy : public analyzer::strategy::AnalyzingStrategy
  {
  public:
    SomeAnalyzingStrategy()
      :analyzer::strategy::AnalyzingStrategy()
    {}
    virtual ~SomeAnalyzingStrategy(){}
    virtual void analyze(const std::shared_ptr<analyzer::definition::DefinitionSource> & definitions, const std::shared_ptr<std::vector<unsigned char>> & data){
      std::this_thread::sleep_for(std::chrono::milliseconds(200));
      
      std::string text;
      for (auto& byte : (*data)){
        text += static_cast<char>(byte);
      }
      
      std::wstring textW(text.begin(), text.end());
      std::vector<std::wstring> tags(findTags(textW));

      for (auto& tag : tags){
        unsigned int id = 0;
        
        for (auto& definition : (*definitions)){
          if (dynamic_cast<TestDef*>(definition.get())->GetExpression().compare(tag) == 0){
            id = definition->GetID();
            break;
          }
        }
        switch (id){
        case 0:
          this->addResult(std::shared_ptr<analyzer::strategy::Result>(new TextResult(TextResult::Classification::unknown, tag)));
          break;

        case 1:
          this->addResult(std::shared_ptr<analyzer::strategy::Result>(new TextResult(TextResult::Classification::checked, tag)));
          break;

        case 2:
          this->addResult(std::shared_ptr<analyzer::strategy::Result>(new TextResult(TextResult::Classification::warning, tag)));
          break;

        case 3:
          this->addResult(std::shared_ptr<analyzer::strategy::Result>(new TextResult(TextResult::Classification::alarm, tag)));
          break;
        }
      }
    }

    virtual bool compareResult(const std::shared_ptr<analyzer::strategy::Result> & result1, const std::shared_ptr<analyzer::strategy::Result> & result2){
      if (dynamic_cast<TextResult*>(result1.get())->GetExpression().compare(dynamic_cast<TextResult*>(result2.get())->GetExpression()) == 0){
        return true;
      }
      else{
        return false;
      }
    }
  };

  void SetUp(){

    defSource.reset(new TestSource());
    
    defSource->AddDefinition(std::shared_ptr<analyzer::definition::Definition>(new TestDef(1, L"checked")));
    defSource->AddDefinition(std::shared_ptr<analyzer::definition::Definition>(new TestDef(2, L"warning")));
    defSource->AddDefinition(std::shared_ptr<analyzer::definition::Definition>(new TestDef(3, L"alarm")));

    data = createData();

    strategy2.SetDefinitions(defSource);
    strategy2.SetData(data);
  }

  SomeAnalyzingStrategy strategy;
  SomeAnalyzingStrategy strategy2;
  std::shared_ptr<analyzer::definition::DefinitionSource> defSource;
  std::shared_ptr<std::vector<unsigned char>> data;
};

TEST_F(AnalyzingStrategyTest, definitions)
{
  strategy.SetDefinitions(defSource);
  ASSERT_TRUE(strategy.HasDefinitionSource());
}

TEST_F(AnalyzingStrategyTest, data)
{
  strategy.SetData(data);
  ASSERT_TRUE(strategy.HasData());
}

TEST_F(AnalyzingStrategyTest, isAnalyzing)
{
  strategy2.StartAnalyzing();
  ASSERT_TRUE(strategy2.IsAnalyzing());
  while (strategy2.IsAnalyzing()){
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}

TEST_F(AnalyzingStrategyTest, results)
{
  strategy2.StartAnalyzing();
  while (strategy2.IsAnalyzing()){
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  ASSERT_EQ(strategy2.GetResults().size(), 5);
}

std::shared_ptr<std::vector<unsigned char>> createData()
{
  std::string fileData;

  fileData += "<checked>this is the checked test</checked>";
  fileData += "<warning>this is the warning test</warning>";
  fileData += "<alarm>this is the alarm test</alarm>";
  fileData += "<unknown1>this is the unknown1 test</unknown1>";
  fileData += "<unknown2>this is the unknown2 test</unknown2>";

  std::shared_ptr<std::vector<unsigned char>> data(new std::vector<unsigned char>(fileData.begin(), fileData.end()));
  return data;
}

std::vector<std::wstring> findTags(const std::wstring & text)
{
  std::vector<std::wstring> tags;
  std::wstring tag;
  bool create = false;

  for (auto& letter : text){
    if (letter == '<'){
      create = true;
      continue;
    }
    if (letter == '>'){
      create = false;
      tags.push_back(tag);
      tag.clear();
      continue;
    }
    if (create && letter != '/'){
      tag += letter;
    }

  }
  return tags;
}

#endif