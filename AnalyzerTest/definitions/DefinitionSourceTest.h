#ifndef DEFINITIONSOURCETEST_H
#define DEFINITIONSOURCETEST_H

#include <gtest\gtest.h>

#include "AnalyzerLib\definitions\DefinitionSource.h"
#include "AnalyzerLib\definitions\TextDefinition.h"

#include "AnalyzerLib\base\error\DBException.h"

class DefinitionSourceTest : public testing::Test
{
public:
  class SomeDefSource : public analyzer::definition::DefinitionSource
  {
  public:
    SomeDefSource()
      : analyzer::definition::DefinitionSource()
    {
      this->setName("some_source");
    }
    virtual ~SomeDefSource(){}

    virtual bool IsInitialized() { return true; }
  };

  void SetUp(){

  }
  SomeDefSource defSource1;
  SomeDefSource defSource2;
};

TEST_F(DefinitionSourceTest, init)
{
  ASSERT_TRUE(defSource1.IsInitialized());
}

TEST_F(DefinitionSourceTest, GetName)
{
  ASSERT_STREQ(defSource1.GetName().c_str(), "some_source");
}

TEST_F(DefinitionSourceTest, AddDefinition)
{
  defSource1.AddDefinition(std::shared_ptr<analyzer::definition::Definition>(new analyzer::definition::TextDefinition(0)));
  ASSERT_EQ(defSource1.GetNumDefinitions(), 1);
}

TEST_F(DefinitionSourceTest, ThrowExistingID)
{
  std::string errorMsg;
  try{
    defSource1.AddDefinition(std::shared_ptr<analyzer::definition::Definition>(new analyzer::definition::TextDefinition(0)));
    defSource1.AddDefinition(std::shared_ptr<analyzer::definition::Definition>(new analyzer::definition::TextDefinition(0)));
  }
  catch (analyzer::base::AnalyzerBaseException & ex){
    errorMsg = std::string(ex.what());
  }
  catch (...){}
  ASSERT_STREQ(errorMsg.c_str(), "ID already in use");
}

TEST_F(DefinitionSourceTest, GetNextFreeID)
{
  ASSERT_EQ(defSource1.GetNextFreeID(), 0);

  defSource1.AddDefinition(std::shared_ptr<analyzer::definition::Definition>(new analyzer::definition::TextDefinition(0)));
  ASSERT_EQ(defSource1.GetNextFreeID(), 1);

  defSource1.AddDefinition(std::shared_ptr<analyzer::definition::Definition>(new analyzer::definition::TextDefinition(1)));
  defSource1.AddDefinition(std::shared_ptr<analyzer::definition::Definition>(new analyzer::definition::TextDefinition(3)));
  ASSERT_EQ(defSource1.GetNextFreeID(), 2);

  defSource1.AddDefinition(std::shared_ptr<analyzer::definition::Definition>(new analyzer::definition::TextDefinition(2)));
  ASSERT_EQ(defSource1.GetNextFreeID(), 4);
}

#endif