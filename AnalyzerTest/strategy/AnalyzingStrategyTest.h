#ifndef ANALYZINGSTRATEGYTEST_H
#define ANALYZINGSTRATEGYTEST_H

#include <gtest/gtest.h>

#include <memory>
#include <string>

#include "AnalyzerLib\strategy\AnalyzingStrategy.h"
#include "AnalyzerLib\definitions\Definition.h"
#include "AnalyzerLib\definitions\DefinitionSource.h"
#include "AnalyzerLib\core\ByteCollection.h"

std::shared_ptr<analyzer::core::ByteCollection> createData();

class AnalyzingStrategyTest : public testing::Test
{
public:
  class TestDef : public analyzer::definition::Definition
  {
  public:
    TestDef(const unsigned int & id, const std::wstring & expression)
      : analyzer::definition::Definition(id), expression(expression)
    {}

    virtual ~TestDef(){}

    void SetExpression(const std::wstring & expression) { this->expression = expression; }
    const std::wstring & GetExpression() const;

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
  };

  void SetUp(){

    defSource.reset(new TestSource());
    
    defSource->AddDefinition(std::shared_ptr<analyzer::definition::Definition>(new TestDef(0, L"checked")));
    defSource->AddDefinition(std::shared_ptr<analyzer::definition::Definition>(new TestDef(1, L"warning")));
    defSource->AddDefinition(std::shared_ptr<analyzer::definition::Definition>(new TestDef(2, L"alarm")));

    data = createData();

  }

  SomeAnalyzingStrategy strategy;
  std::shared_ptr<analyzer::definition::DefinitionSource> defSource;
  std::shared_ptr<analyzer::core::ByteCollection> data;
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

std::shared_ptr<analyzer::core::ByteCollection> createData()
{
  std::string fileData;

  fileData += "<checked>this is the checked test</checked>";
  fileData += "<warning>this is the warning test</warning>";
  fileData += "<alarm>this is the alarm test</alarm>";
  fileData += "<unknown1>this is the unknown1 test</unknown1>";
  fileData += "<unknown2>this is the unknown2 test</unknown2>";

  std::shared_ptr<analyzer::core::ByteCollection> data(new analyzer::core::ByteCollection(fileData.c_str(), fileData.size()));
  return data;
}

#endif