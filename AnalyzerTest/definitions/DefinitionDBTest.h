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
  db.Connect("127.0.0.1", 3306, "root", "toor");
  ASSERT_TRUE(db.IsInitialized());
}

TEST_F(DefinitionDBTest, DBException)
{
  bool dbExceptionThrown = false;

  try{
    analyzer::definition::DefinitionDB db;
    db.Connect("127.0.0.1", 3306, "root", "wrong");
  }
  catch (analyzer::base::DBException & exception){
    dbExceptionThrown = true;
  }
  catch (...){}
  ASSERT_TRUE(dbExceptionThrown);
}

#endif