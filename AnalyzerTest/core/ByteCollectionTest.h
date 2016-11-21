#include <gtest/gtest.h>

#include <string>

#include "AnalyzerLib\core\Byte.h"
#include "AnalyzerLib\core\ByteCollection.h"

TEST(ByteCollectionTest, EmptyOnDefaultInit)
{
  analyzer::core::ByteCollection byteCollection;
  ASSERT_EQ(byteCollection.GetSize(), 0);
}

TEST(ByteCollectionTest, InitByCharArray)
{
  char bytes[10] = { 0 };
  analyzer::core::ByteCollection byteCollection(bytes, 10);
  ASSERT_EQ(byteCollection.GetSize(), 10);
}

TEST(ByteCollectionTest, GetByteAt)
{
  char bytes[10] = { 0 };
  bytes[3] = 42;
  analyzer::core::ByteCollection byteCollection(bytes, 10);
  analyzer::core::Byte testByte(42);
  ASSERT_EQ(byteCollection.GetByteAt(3), testByte);
}

TEST(ByteCollectionTest, IndexMissmatch)
{
  char bytes[10] = { 0 };
  analyzer::core::ByteCollection byteCollection(bytes, 10);

  try{
    byteCollection.GetByteAt(42);
  }
  catch (analyzer::core::CoreException const & ex){
    ASSERT_STREQ(ex.what(), "Byte index out of range");
    return;
  }
  FAIL() << "Expected core exception";
}

TEST(ByteCollectionTest, Iterate)
{
  char bytes[10] = { 0,1,2,3,4,5,6,7,8,9 };

  analyzer::core::ByteCollection byteCollection(bytes, 10);
  size_t index = 0;
  for (auto& byte : byteCollection){
    ASSERT_EQ(byteCollection.GetByteAt(index).GetValue(), index);
    index++;
  }
  
}