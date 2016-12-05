#ifndef BYTECOLLECTIONTEST_H
#define BYTECOLLECTIONTEST_H

#include <gtest/gtest.h>

#include <string>

#include "AnalyzerLib\core\Byte.h"
#include "AnalyzerLib\core\ByteCollection.h"
#include "AnalyzerLib\core\error\CoreException.h"

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

TEST(ByteCollectionTest, InitByCharVector)
{
  std::vector<char> bytes;
  bytes.push_back('a');
  bytes.push_back('a');
  bytes.push_back('a');
  bytes.push_back('a');

  analyzer::core::ByteCollection byteCollection(bytes);
  ASSERT_EQ(byteCollection.GetSize(), 4);
}

TEST(ByteCollectionTest, GetByteAt)
{
  char bytes[10] = { 0 };
  bytes[3] = 42;
  analyzer::core::ByteCollection byteCollection(bytes, 10);
  analyzer::core::Byte testByte(42);
  ASSERT_EQ(*byteCollection.GetByteAt(3).get(), testByte);
}

TEST(ByteCollectionTest, IndexMissmatch)
{
  char bytes[10] = { 0 };
  analyzer::core::ByteCollection byteCollection(bytes, 10);

  try{
    byteCollection.GetByteAt(42);
  }
  catch (analyzer::core::CoreException & ex){
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
    ASSERT_EQ(byteCollection.GetByteAt(index)->GetValue(), index);
    index++;
  }
}

TEST(ByteCollectionTest, AsSharedPtr)
{
  char bytes[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

  std::shared_ptr<analyzer::core::ByteCollection> byteCollection(new analyzer::core::ByteCollection(bytes, 10));
  size_t index = 0;
  for (auto byte : *byteCollection.get()){
    ASSERT_EQ(byteCollection->GetByteAt(index)->GetValue(), index);
    index++;
  }
}

#endif