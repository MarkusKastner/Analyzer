#include <gtest/gtest.h>

#include <string>

#include "AnalyzerLib\core\Byte.h"

TEST(BasicTypeTest, GetBitsAsString)
{
  analyzer::core::BasicType * byte = new analyzer::core::Byte(255);

  ASSERT_STREQ(byte->GetBitsAsString().c_str(), std::string("11111111").c_str());
}

TEST(BasicTypeTest, GetBitAt)
{
  analyzer::core::BasicType * byte = new analyzer::core::Byte(255);

  ASSERT_EQ(byte->GetBitAt(0), static_cast<unsigned int>(1));
}