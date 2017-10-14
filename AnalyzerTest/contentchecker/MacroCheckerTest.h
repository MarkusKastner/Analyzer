/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef MACROCHECKERTEST_H
#define MACROCHECKERTEST_H

#include <gtest/gtest.h>
#include "TestSupport.h"

#include "AnalyzerLib/contentchecker/MacroChecker.h"

class MacroCheckerTest : public testing::Test
{
public:
  MacroCheckerTest()
    : testing::Test(), syntaxData1(new std::vector<unsigned char>()), jsSyntaxDef()
  {
  }

  void SetUp() {
    for (int i = 0; i < 10; ++i) {
      this->syntaxData1->push_back(static_cast<unsigned char>(i));
    }
    this->syntaxData1->push_back('i');
    this->syntaxData1->push_back('f');
    this->syntaxData1->push_back(' ');
    this->syntaxData1->push_back('(');
    this->syntaxData1->push_back('t');
    this->syntaxData1->push_back('r');
    this->syntaxData1->push_back('u');
    this->syntaxData1->push_back('e');
    this->syntaxData1->push_back(')');
    this->syntaxData1->push_back(' ');
    this->syntaxData1->push_back('{');
    for (int i = 10; i < 20; ++i) {
      this->syntaxData1->push_back(static_cast<unsigned char>(i));
    }
    this->jsSyntaxDef = TestSupport::GetInstance()->GetDataFromTestFilesDir("jsSyntaxDef.txt");
  }

  virtual ~MacroCheckerTest() {
  }

  std::shared_ptr<std::vector<unsigned char>> syntaxData1;
  std::shared_ptr<std::vector<unsigned char>> jsSyntaxDef;
};

TEST_F(MacroCheckerTest, init)
{
  analyzer::checker::MacroChecker checker;
  ASSERT_FALSE(checker.HasData());
}

TEST_F(MacroCheckerTest, nextSyntaxHint)
{
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->syntaxData1);
  ASSERT_EQ(checker.FindNextSyntaxHint(), 10);
}

TEST_F(MacroCheckerTest, jsAstractSyntax)
{
  size_t startOffset = 0;
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->jsSyntaxDef);
  ASSERT_TRUE(checker.IsACaseSyntax(startOffset));
  ASSERT_STREQ(checker.RangeToString(startOffset, checker.GetLastFoundSyntaxOffset()).c_str(), analyzer::checker::MacroChecker::KeyWord_abstract.c_str());
}

TEST_F(MacroCheckerTest, jsArgumentsSyntax)
{
  size_t startOffset = 10;
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->jsSyntaxDef);
  ASSERT_TRUE(checker.IsACaseSyntax(startOffset));
  ASSERT_STREQ(checker.RangeToString(startOffset, checker.GetLastFoundSyntaxOffset()).c_str(), analyzer::checker::MacroChecker::KeyWord_arguments.c_str());
}

TEST_F(MacroCheckerTest, jsAwaitSyntax)
{
  size_t startOffset = 21;
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->jsSyntaxDef);
  ASSERT_TRUE(checker.IsACaseSyntax(startOffset));
  ASSERT_STREQ(checker.RangeToString(startOffset, checker.GetLastFoundSyntaxOffset()).c_str(), analyzer::checker::MacroChecker::KeyWord_await.c_str());
}

TEST_F(MacroCheckerTest, jsBooleanSyntax)
{
  size_t startOffset = 29;
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->jsSyntaxDef);
  ASSERT_TRUE(checker.IsBCaseSyntax(startOffset));
  ASSERT_STREQ(checker.RangeToString(startOffset, checker.GetLastFoundSyntaxOffset()).c_str(), analyzer::checker::MacroChecker::KeyWord_boolean.c_str());
}

TEST_F(MacroCheckerTest, jsBreakSyntax)
{
  size_t startOffset = 38;
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->jsSyntaxDef);
  ASSERT_TRUE(checker.IsBCaseSyntax(startOffset));
  ASSERT_STREQ(checker.RangeToString(startOffset, checker.GetLastFoundSyntaxOffset()).c_str(), analyzer::checker::MacroChecker::KeyWord_break.c_str());
}

TEST_F(MacroCheckerTest, jsByteSyntax)
{
  size_t startOffset = 46;
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->jsSyntaxDef);
  ASSERT_TRUE(checker.IsBCaseSyntax(startOffset));
  ASSERT_STREQ(checker.RangeToString(startOffset, checker.GetLastFoundSyntaxOffset()).c_str(), analyzer::checker::MacroChecker::KeyWord_byte.c_str());
}

TEST_F(MacroCheckerTest, jsCaseSyntax)
{
  size_t startOffset = 53;
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->jsSyntaxDef);
  ASSERT_TRUE(checker.IsCCaseSyntax(startOffset));
  ASSERT_STREQ(checker.RangeToString(startOffset, checker.GetLastFoundSyntaxOffset()).c_str(), analyzer::checker::MacroChecker::KeyWord_case.c_str());
}

TEST_F(MacroCheckerTest, jsCatchSyntax)
{
  size_t startOffset = 60;
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->jsSyntaxDef);
  ASSERT_TRUE(checker.IsCCaseSyntax(startOffset));
  ASSERT_STREQ(checker.RangeToString(startOffset, checker.GetLastFoundSyntaxOffset()).c_str(), analyzer::checker::MacroChecker::KeyWord_catch.c_str());
}

TEST_F(MacroCheckerTest, jsCharSyntax)
{
  size_t startOffset = 67;
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->jsSyntaxDef);
  ASSERT_TRUE(checker.IsCCaseSyntax(startOffset));
  ASSERT_STREQ(checker.RangeToString(startOffset, checker.GetLastFoundSyntaxOffset()).c_str(), analyzer::checker::MacroChecker::KeyWord_char.c_str());
}

TEST_F(MacroCheckerTest, jsClassSyntax)
{
  size_t startOffset = 74;
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->jsSyntaxDef);
  ASSERT_TRUE(checker.IsCCaseSyntax(startOffset));
  ASSERT_STREQ(checker.RangeToString(startOffset, checker.GetLastFoundSyntaxOffset()).c_str(), analyzer::checker::MacroChecker::KeyWord_class.c_str());
}

TEST_F(MacroCheckerTest, jsConstSyntax)
{
  size_t startOffset = 83;
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->jsSyntaxDef);
  ASSERT_TRUE(checker.IsCCaseSyntax(startOffset));
  ASSERT_STREQ(checker.RangeToString(startOffset, checker.GetLastFoundSyntaxOffset()).c_str(), analyzer::checker::MacroChecker::KeyWord_const.c_str());
}

TEST_F(MacroCheckerTest, jsContinueSyntax)
{
  size_t startOffset = 91;
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->jsSyntaxDef);
  ASSERT_TRUE(checker.IsCCaseSyntax(startOffset));
  ASSERT_STREQ(checker.RangeToString(startOffset, checker.GetLastFoundSyntaxOffset()).c_str(), analyzer::checker::MacroChecker::KeyWord_continue.c_str());
}

TEST_F(MacroCheckerTest, jsDebuggerSyntax)
{
  size_t startOffset = 101;
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->jsSyntaxDef);
  ASSERT_TRUE(checker.IsDCaseSyntax(startOffset));
  ASSERT_STREQ(checker.RangeToString(startOffset, checker.GetLastFoundSyntaxOffset()).c_str(), analyzer::checker::MacroChecker::KeyWord_debugger.c_str());
}

TEST_F(MacroCheckerTest, jsDefaultSyntax)
{
  size_t startOffset = 112;
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->jsSyntaxDef);
  ASSERT_TRUE(checker.IsDCaseSyntax(startOffset));
  ASSERT_STREQ(checker.RangeToString(startOffset, checker.GetLastFoundSyntaxOffset()).c_str(), analyzer::checker::MacroChecker::KeyWord_default.c_str());
}

TEST_F(MacroCheckerTest, jsDeleteSyntax)
{
  size_t startOffset = 122;
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->jsSyntaxDef);
  ASSERT_TRUE(checker.IsDCaseSyntax(startOffset));
  ASSERT_STREQ(checker.RangeToString(startOffset, checker.GetLastFoundSyntaxOffset()).c_str(), analyzer::checker::MacroChecker::KeyWord_delete.c_str());
}

TEST_F(MacroCheckerTest, jsDoSyntax)
{
  size_t startOffset = 131;
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->jsSyntaxDef);
  ASSERT_TRUE(checker.IsDCaseSyntax(startOffset));
  ASSERT_STREQ(checker.RangeToString(startOffset, checker.GetLastFoundSyntaxOffset()).c_str(), analyzer::checker::MacroChecker::KeyWord_do.c_str());
}

TEST_F(MacroCheckerTest, jsDoubleSyntax)
{
  size_t startOffset = 135;
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->jsSyntaxDef);
  ASSERT_TRUE(checker.IsDCaseSyntax(startOffset));
  ASSERT_STREQ(checker.RangeToString(startOffset, checker.GetLastFoundSyntaxOffset()).c_str(), analyzer::checker::MacroChecker::KeyWord_double.c_str());
}


#endif
