/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include <gtest/gtest.h>

#include <string>

#include "AnalyzerLib\core\Word.h"
#include "AnalyzerLib\core\error\CoreException.h"

TEST(WordTest, InitialDefaultWord)
{
  analyzer::core::Word word;

  ASSERT_EQ(word.GetValue(), 0);
}

TEST(WordTest, InitialBytes1)
{
  analyzer::core::Byte highByte(0);
  analyzer::core::Byte lowByte(1);
  analyzer::core::Word word(highByte, lowByte);

  ASSERT_EQ(word.GetValue(), 1);
}

TEST(WordTest, InitialBytes256)
{
  analyzer::core::Byte highByte(3);
  analyzer::core::Byte lowByte(0);
  analyzer::core::Word word(highByte, lowByte);

  ASSERT_EQ(word.GetValue(), 768);
}

TEST(WordTest, GetBitInLowByte)
{
  analyzer::core::Byte highByte(3);
  analyzer::core::Byte lowByte(7);
  analyzer::core::Word word(highByte, lowByte);

  ASSERT_EQ(word.GetBitAt(2), 1);
}

TEST(WordTest, GetBitInHighByte)
{
  analyzer::core::Byte highByte(3);
  analyzer::core::Byte lowByte(255);
  analyzer::core::Word word(highByte, lowByte);

  ASSERT_EQ(word.GetBitAt(12), 0);
}

TEST(WordTest, GetBitIndexOutOfRange)
{
  analyzer::core::Word word;

  try{
    word.GetBitAt(42);
  }
  catch (analyzer::core::CoreException const & ex){
    ASSERT_STREQ(ex.what(), "Bit index out of range");
    return;
  }
  FAIL() << "Expected core exception";
}

TEST(WordTest, GetWordAsString)
{
  analyzer::core::Byte highByte(3);
  analyzer::core::Byte lowByte(255);
  analyzer::core::Word word(highByte, lowByte);

  ASSERT_STREQ(word.GetBitsAsString().c_str(), std::string("00000011 11111111").c_str());
}