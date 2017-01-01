#ifndef DEFINITIONTEST_H
#define DEFINITIONTEST_H

#include <gtest\gtest.h>

#include "AnalyzerLib\definitions\Definition.h"

class DefinitionTest : public testing::Test
{

};

TEST_F(DefinitionTest, init)
{
  analyzer::definition::Definition definition(0);
  ASSERT_EQ(definition.GetID(), 0);
}

#endif