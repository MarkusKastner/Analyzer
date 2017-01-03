#ifndef ANALYZINGSTRATEGYTEST_H
#define ANALYZINGSTRATEGYTEST_H

#include <gtest/gtest.h>

#include "AnalyzerLib\strategy\AnalyzingStrategy.h"
#include "AnalyzerLib\definitions\Definition.h"
#include "AnalyzerLib\definitions\DefinitionSource.h"
#include "AnalyzerLib\core\ByteCollection.h"

#include <memory>

class AnalyzingStrategyTest : public testing::Test
{
public:
  class TestDef : public analyzer::definition::Definition
  {
  public:
    TestDef(const unsigned int & id)
      : analyzer::definition::Definition(id)
    {}

    virtual ~TestDef(){}
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
    data.reset(new analyzer::core::ByteCollection());
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

#endif