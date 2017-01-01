#ifndef DEFINITIONTEST_H
#define DEFINITIONTEST_H

#include <gtest\gtest.h>

#include "AnalyzerLib\definitions\Definition.h"

class DefinitionTest : public testing::Test
{
public:

  void SetUp(){
    def1.reset(new analyzer::definition::Definition(0));
  }
  std::shared_ptr<analyzer::definition::Definition> def1;
};

TEST_F(DefinitionTest, init)
{
  analyzer::definition::Definition definition(0);
  ASSERT_EQ(definition.GetID(), 0);
}

TEST_F(DefinitionTest, description)
{
  def1->SetDescription("a description");
  ASSERT_STREQ(def1->GetDescription().c_str(), "a description");
}

#endif