#ifndef TEXTDEFINITIONTEST_H
#define TEXTDEFINITIONTEST_H

#include <gtest\gtest.h>

#include "AnalyzerLib\definitions\TextDefinition.h"

class TextDefinitionTest : public testing::Test
{
public:
  void SetUp(){
    def1.reset(new analyzer::definition::TextDefinition(0));
  }
  std::shared_ptr<analyzer::definition::TextDefinition> def1;
};

TEST_F(TextDefinitionTest, init)
{
  ASSERT_EQ(def1->GetID(), 0);
}

TEST_F(TextDefinitionTest, expression)
{
  def1->SetExpression("a");
  ASSERT_STREQ(def1->GetExpression().c_str(), "a");
}

#endif