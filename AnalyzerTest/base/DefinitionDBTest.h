#ifndef DEFINITIONDBTEST_H
#define DEFINITIONDBTEST_H

#include <gtest\gtest.h>

#include "AnalyzerLib\base\DefinitionDB.h"

class DefinitionDBTest : public testing::Test
{

};

TEST_F(DefinitionDBTest, ConnectDB)
{
  analyzer::base::DefinitionDB db;
  db.Connect("127.0.0.1", 3306, "root", "toor");
  ASSERT_TRUE(db.IsConnected());
}

#endif