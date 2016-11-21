#include <gtest/gtest.h>

#include <string>
#include <memory>

#include "AnalyzerLib\interpreter\BinaryStyleInterpreter.h"
#include "AnalyzerLib\core\ByteCollection.h"

TEST(BinaryStyleInterpreterTest, AbstractImplEmptyOnDefaultCtor)
{
  std::unique_ptr<analyzer::interpreter::Interpreter>  interpreter(new analyzer::interpreter::BinaryStyleInterpreter());
  ASSERT_EQ(interpreter->HasData(), false);
}

TEST(BinaryStyleInterpreterTest, CtorEmptyByteCollection)
{
  std::shared_ptr<analyzer::core::ByteCollection> byteCollection(new analyzer::core::ByteCollection());
  analyzer::interpreter::BinaryStyleInterpreter  interpreter(byteCollection);
  ASSERT_EQ(interpreter.HasData(), false);
}

TEST(BinaryStyleInterpreterTest, CtorHasData)
{
  char bytes[10] = { 0 };
  std::shared_ptr<analyzer::core::ByteCollection> byteCollection(new analyzer::core::ByteCollection(bytes, 10));
  analyzer::interpreter::BinaryStyleInterpreter  interpreter(byteCollection);
  ASSERT_EQ(interpreter.HasData(), true);
}