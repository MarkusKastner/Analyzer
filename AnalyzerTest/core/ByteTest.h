#include <gtest/gtest.h>

#include <string>

#include "AnalyzerLib\core\Byte.h"
#include "AnalyzerLib\core\error\CoreException.h"

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

TEST(ByteTest, GetBitsAsString1)
{
  analyzer::core::Byte byte(255);

  ASSERT_STREQ(byte.GetBitsAsString().c_str(), std::string("11111111").c_str());
}

TEST(ByteTest, GetBitsAsString2)
{
  analyzer::core::Byte byte(1);

  ASSERT_STREQ(byte.GetBitsAsString().c_str(), std::string("00000001").c_str());
}

TEST(ByteTest, GetBitIndexOutOfRange)
{
  analyzer::core::Byte byte(255);
  try{
    byte.GetBitAt(42);
  }
  catch (analyzer::core::CoreException const & ex){
    ASSERT_STREQ(ex.what(), "Bit index out of range");
    return;
  }
  FAIL() << "Expected core exception";
}