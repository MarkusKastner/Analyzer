#ifndef TEXTDEFINITIONTEST_H
#define TEXTDEFINITIONTEST_H

#include <gtest\gtest.h>

#include "AnalyzerLib\definitions\TextDefinition.h"

class TextDefinitionTest : public testing::Test
{
public:


};

TEST_F(TextDefinitionTest, init)
{
  analyzer::definition::TextDefinition def(0);
  ASSERT_EQ(def.GetID(), 0);
}
#endif