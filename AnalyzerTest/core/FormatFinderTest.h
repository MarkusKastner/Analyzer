#ifndef FORMATFINDERTEST_H
#define FORMATFINDERTEST_H

#include <gtest\gtest.h>

#include <memory>

#include "AnalyzerLib\core\ByteCollection.h"
#include "AnalyzerLib\core\FormatFinder.h"

class FormatFinderTest : public testing::Test
{
public:
  std::shared_ptr<analyzer::core::ByteCollection> createASCIITextData()
  {
    std::string fileData;

    fileData += "this is just some ascii text.";

    std::shared_ptr<analyzer::core::ByteCollection> data(new analyzer::core::ByteCollection(fileData.c_str(), fileData.size()));
    return data;
  }

  analyzer::core::FormatFinder finder;
};

TEST_F(FormatFinderTest, identifyASCII)
{
  ASSERT_EQ(finder.Analyze(this->createASCIITextData()), analyzer::core::FormatFinder::Format::ascii);
}

#endif