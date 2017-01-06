#ifndef FORMATFINDERTEST_H
#define FORMATFINDERTEST_H

#include <gtest\gtest.h>

#include <memory>

#include "AnalyzerLib\core\ByteCollection.h"
#include "AnalyzerLib\core\FormatFinder.h"

class FormatFinderTest : public testing::Test
{
public:
  std::shared_ptr<analyzer::core::ByteCollection> createTextData1()
  {
    std::string fileData;
    fileData += "some text.\n";
    fileData += "üהצß/&%$§ית\n";
    std::shared_ptr<analyzer::core::ByteCollection> data(new analyzer::core::ByteCollection(fileData.c_str(), fileData.size()));
    return data;
  }

  std::shared_ptr<analyzer::core::ByteCollection> createXMLData()
  {
    std::string fileData("<?xml version=\"1.0\"?>");
    std::shared_ptr<analyzer::core::ByteCollection> data(new analyzer::core::ByteCollection(fileData.c_str(), fileData.size()));
    return data;
  }

  void SetUp(){

  }

  analyzer::core::FormatFinder finder;
};

TEST_F(FormatFinderTest, isText)
{
  finder.SetData(createTextData1());
  finder.Analyze();
  ASSERT_EQ(finder.GetBaseFormat(), analyzer::core::FormatFinder::Format::text);
}

TEST_F(FormatFinderTest, isXML)
{
  finder.SetData(createXMLData());
  finder.Analyze();
  ASSERT_EQ(finder.GetDetailFormat(), analyzer::core::FormatFinder::Format::xml);
}

#endif