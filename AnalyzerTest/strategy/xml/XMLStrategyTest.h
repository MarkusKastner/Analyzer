/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef XMLSTRATEGYTEST_H
#define XMLSTRATEGYTEST_H

#include <gtest\gtest.h>

#include <memory>

#include "AnalyzerLib\strategy\xml\XMLStrategy.h"
#include "AnalyzerLib\core\ByteCollection.h"

#include "AnalyzerLib\definitions\Definition.h"
#include "AnalyzerLib\definitions\DefinitionSource.h"

std::shared_ptr<analyzer::core::ByteCollection> createXMLData();

class XMLStrategyTest : public testing::Test
{
public:
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

  void SetUp(){

    defSource.reset(new TestSource());
    data = createData();

  }

  analyzer::strategy::XMLStrategy xmlStrategy;
  std::shared_ptr<analyzer::definition::DefinitionSource> defSource;
  std::shared_ptr<analyzer::core::ByteCollection> data;
};

TEST_F(XMLStrategyTest, init)
{
  

}

std::shared_ptr<analyzer::core::ByteCollection> createXMLData()
{
  std::string fileData;
  fileData += "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\" ?>";
  fileData += "<someDoc>";
  fileData += "<checked>this is the checked test</checked>";
  fileData += "<warning>this is the warning test</warning>";
  fileData += "<alarm>this is the alarm test</alarm>";
  fileData += "<unknown1>this is the unknown1 test</unknown1>";
  fileData += "<unknown2>this is the unknown2 test</unknown2>";
  fileData += "</someDoc>";

  std::shared_ptr<analyzer::core::ByteCollection> data(new analyzer::core::ByteCollection(fileData.c_str(), fileData.size()));
  return data;
}
#endif