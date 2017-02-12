#ifndef TYPEANALYZERTEST_H
#define TYPEANALYZERTEST_H

#include <gtest\gtest.h>
#include <memory>
#include <vector>

#include "AnalyzerLib\core\TypeAnalyzer.h"
#include "AnalyzerLib\core\FileInfo.h"
#include "TestSupport.h"

class TypeAnalyzerTest : public testing::Test
{
public:
  TypeAnalyzerTest() {}
  virtual ~TypeAnalyzerTest() {}


};

TEST_F(TypeAnalyzerTest, emptyData)
{
  auto fileInfo = analyzer::core::TypeAnalyzer::GetInstance()->GetFileInfo(std::shared_ptr<std::vector<unsigned char>>());
  ASSERT_EQ(fileInfo.majorType, analyzer::core::MajorType::empty);
}

TEST_F(TypeAnalyzerTest, recXML)
{
  auto data = TestSupport::GetInstance()->GetDataFromTestFilesDir("test.xml");
  auto fileInfo = analyzer::core::TypeAnalyzer::GetInstance()->GetFileInfo(data);
  ASSERT_EQ(fileInfo.majorType, analyzer::core::MajorType::text);
  ASSERT_EQ(fileInfo.minorType, analyzer::core::MinorType::xml);
}

#endif