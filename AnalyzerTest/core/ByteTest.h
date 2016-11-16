#include <gtest/gtest.h>

#include <string>

#include "AnalyzerLib\core\Byte.h"

TEST(ByteTest, InitialDefaultByte)
{
  analyzer::core::Byte byte;

  ASSERT_EQ(byte.GetValue(), static_cast<const char>(0));
}

TEST(ByteTest, InitialValueByte)
{
  analyzer::core::Byte byte(1);

  ASSERT_EQ(byte.GetValue(), static_cast<const char>(1));
}

TEST(ByteTest, GetBitAt0)
{
  analyzer::core::Byte byte(255);

  ASSERT_EQ(byte.GetBitAt(0), static_cast<unsigned int>(1));
}

TEST(ByteTest, GetBitsAsString)
{
  analyzer::core::Byte byte(255);

  ASSERT_STREQ(byte.GetBitsAsString().c_str(), std::string("11111111").c_str());
}