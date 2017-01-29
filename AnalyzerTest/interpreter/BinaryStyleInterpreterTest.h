/* Copyright (C) 2016-2017 - All Rights Reserved
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
#include "AnalyzerLib\interpreter\error\InterpreterException.h"

class BinaryStyleInterpreterTest : public testing::Test
{
public:
  BinaryStyleInterpreterTest()
    : data1(new std::vector<unsigned char>()), data2(new std::vector<unsigned char>({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 })), data3(new std::vector<unsigned char>({ 0, 1, 2, 3, 4 })),
    charVector(new std::vector<unsigned char>())
  {}

  ~BinaryStyleInterpreterTest()
  {
  }

  void SetUp(){
    for (int i = 0; i < 5; i++){
      this->charVector->push_back('a');
    }
  }

  std::shared_ptr<std::vector<unsigned char>> data1;
  std::shared_ptr<std::vector<unsigned char>> data2;
  std::shared_ptr<std::vector<unsigned char>> data3;
  std::shared_ptr<std::vector<unsigned char>> charVector;
};

TEST_F(BinaryStyleInterpreterTest, AbstractImplEmptyOnDefaultCtor)
{
  std::unique_ptr<analyzer::interpreter::Interpreter> interpreter(new analyzer::interpreter::BinaryStyleInterpreter());
  ASSERT_FALSE(interpreter->HasData());
}

TEST_F(BinaryStyleInterpreterTest, CtorEmptyByteCollection)
{
  analyzer::interpreter::BinaryStyleInterpreter interpreter(this->data1);
  ASSERT_FALSE(interpreter.HasData());
}

TEST_F(BinaryStyleInterpreterTest, CtorHasData)
{
  analyzer::interpreter::BinaryStyleInterpreter interpreter(this->data2);
  ASSERT_EQ(interpreter.HasData(), true);
}

TEST_F(BinaryStyleInterpreterTest, ResetDataByteCollection)
{
  analyzer::interpreter::BinaryStyleInterpreter interpreter(this->data2);
  size_t sizePreReset = interpreter.GetData()->size();
  interpreter.ResetData(this->data3);

  ASSERT_FALSE(interpreter.GetData()->size() == sizePreReset);
}

TEST_F(BinaryStyleInterpreterTest, ResetDataCharVector)
{
  analyzer::interpreter::BinaryStyleInterpreter interpreter(this->data2);
  size_t sizePreReset = interpreter.GetData()->size();
  interpreter.ResetData(this->charVector);

  ASSERT_FALSE(interpreter.GetData()->size() == sizePreReset);
}

TEST_F(BinaryStyleInterpreterTest, PlainText)
{
  std::shared_ptr<std::vector<unsigned char>> bytes(new std::vector<unsigned char>({ 0, 0 }));
  
  analyzer::interpreter::BinaryStyleInterpreter interpreter(bytes);
  ASSERT_STREQ(interpreter.GetText()->c_str(), std::wstring(L"00000000  00000000                        [000][000]").c_str());
}

TEST_F(BinaryStyleInterpreterTest, PlainTextOnEmptyByteCollection)
{
  analyzer::interpreter::BinaryStyleInterpreter interpreter;
  ASSERT_STREQ(interpreter.GetText()->c_str(), std::wstring().c_str());
}

#endif