/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef LOCALDEFINITIONTEST_H
#define LOCALDEFINITIONTEST_H

#include <gtest\gtest.h>

#include "AnalyzerLib\definitions\LocalDefinition.h"

#include "AnalyzerLib\base\error\DBException.h"

class LocalDefinitionTest : public testing::Test
{
public:

};

TEST_F(LocalDefinitionTest, init)
{
  analyzer::definition::LocalDefinition localSource;
  ASSERT_TRUE(localSource.IsInitialized());
}

TEST_F(LocalDefinitionTest, initNamedResource)
{
  analyzer::definition::LocalDefinition localSource("source_name");
  ASSERT_STREQ(localSource.GetName().c_str(), "source_name");
}

#endif