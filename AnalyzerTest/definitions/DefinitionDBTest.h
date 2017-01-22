/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef DEFINITIONDBTEST_H
#define DEFINITIONDBTEST_H

#include <gtest\gtest.h>

#include "AnalyzerLib\definitions\DefinitionDB.h"
#include "AnalyzerLib\base\error\DBException.h"

class DefinitionDBTest : public testing::Test
{

};

TEST_F(DefinitionDBTest, ConnectDB)
{
  analyzer::definition::DefinitionDB db;
  ASSERT_FALSE(db.IsInitialized());
}


#endif