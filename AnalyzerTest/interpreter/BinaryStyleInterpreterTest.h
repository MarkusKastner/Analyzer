/* Copyright (C) 2016 - 2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef BINARYSTYLEINTERPRETERTEST_H
#define BINARYSTYLEINTERPRETERTEST_H

#include <gtest/gtest.h>

#include <string>
#include <memory>

#include "AnalyzerLib\interpreter\BinaryStyleInterpreter.h"
#include "AnalyzerLib\core\ByteCollection.h"
#include "AnalyzerLib\interpreter\error\InterpreterException.h"

class BinaryStyleInterpreterTest : public testing::Test
{
public:
  BinaryStyleInterpreterTest()
    : bytes2(nullptr), numBytes2(10), bytes3(nullptr), numBytes3(5),
    byteCollection1(new analyzer::core::ByteCollection()), 
    byteCollection2(),
    byteCollection3(),
    charVector()
  {}

  ~BinaryStyleInterpreterTest()
  {
    if (this->bytes2 != nullptr){
      delete[] this->bytes2;
      this->bytes2 = nullptr;
    }
  }

  void SetUp(){
    this->bytes2 = new char[numBytes2]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    this->bytes3 = new char[numBytes3]{0, 1, 2, 3, 4};

    std::vector<std::shared_ptr<analyzer::core::Byte>> tetBytes;
    tetBytes.push_back(std::shared_ptr<analyzer::core::Byte>(new analyzer::core::Byte(0)));


    this->byteCollection2.reset(new analyzer::core::ByteCollection(bytes2, numBytes2));
    this->byteCollection3.reset(new analyzer::core::ByteCollection(bytes3, numBytes3));

    for (int i = 0; i < 5; i++){
      this->charVector.push_back('a');
    }
  }

  char * bytes2;
  size_t numBytes2;

  char * bytes3;
  size_t numBytes3;

  std::shared_ptr<analyzer::core::ByteCollection> byteCollection1;
  std::shared_ptr<analyzer::core::ByteCollection> byteCollection2;
  std::shared_ptr<analyzer::core::ByteCollection> byteCollection3;
  std::vector<char> charVector;
};

TEST_F(BinaryStyleInterpreterTest, AbstractImplEmptyOnDefaultCtor)
{
  std::unique_ptr<analyzer::interpreter::Interpreter> interpreter(new analyzer::interpreter::BinaryStyleInterpreter());
  ASSERT_EQ(interpreter->HasData(), false);
}

TEST_F(BinaryStyleInterpreterTest, CtorEmptyByteCollection)
{
  analyzer::interpreter::BinaryStyleInterpreter interpreter(this->byteCollection1);
  ASSERT_EQ(interpreter.HasData(), false);
}

TEST_F(BinaryStyleInterpreterTest, CtorHasData)
{
  analyzer::interpreter::BinaryStyleInterpreter  interpreter(this->byteCollection2);
  ASSERT_EQ(interpreter.HasData(), true);
}

TEST_F(BinaryStyleInterpreterTest, ResetDataByteCollection)
{
  analyzer::interpreter::BinaryStyleInterpreter interpreter(this->byteCollection2);
  size_t sizePreReset = interpreter.GetData()->GetSize();
  interpreter.ResetData(this->byteCollection3);

  ASSERT_FALSE(interpreter.GetData()->GetSize() == sizePreReset);
}

TEST_F(BinaryStyleInterpreterTest, ResetDataCharVector)
{
  analyzer::interpreter::BinaryStyleInterpreter interpreter(this->byteCollection2);
  size_t sizePreReset = interpreter.GetData()->GetSize();
  interpreter.ResetData(this->charVector);

  ASSERT_FALSE(interpreter.GetData()->GetSize() == sizePreReset);
}

TEST_F(BinaryStyleInterpreterTest, PlainText)
{
  const char bytes[2] { 0, 0 };

  std::shared_ptr<analyzer::core::ByteCollection> byteCollection(new analyzer::core::ByteCollection(bytes, 2));

  analyzer::interpreter::BinaryStyleInterpreter interpreter(byteCollection);

  ASSERT_STREQ(interpreter.GetText()->c_str(), std::wstring(L"00000000  00000000                        [000][000]").c_str());
}

TEST_F(BinaryStyleInterpreterTest, PlainTextOnEmptyByteCollection)
{
  analyzer::interpreter::BinaryStyleInterpreter interpreter;
  ASSERT_STREQ(interpreter.GetText()->c_str(), std::wstring().c_str());
}

#endif