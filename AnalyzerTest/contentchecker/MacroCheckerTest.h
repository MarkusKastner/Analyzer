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

TEST_F(MacroCheckerTest, jsElseSyntax)
{
  size_t startOffset = 144;
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->jsSyntaxDef);
  ASSERT_TRUE(checker.IsECaseSyntax(startOffset));
  ASSERT_STREQ(checker.RangeToString(startOffset, checker.GetLastFoundSyntaxOffset()).c_str(), analyzer::checker::MacroChecker::KeyWord_else.c_str());
}

TEST_F(MacroCheckerTest, jsEnumSyntax)
{
  size_t startOffset = 151;
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->jsSyntaxDef);
  ASSERT_TRUE(checker.IsECaseSyntax(startOffset));
  ASSERT_STREQ(checker.RangeToString(startOffset, checker.GetLastFoundSyntaxOffset()).c_str(), analyzer::checker::MacroChecker::KeyWord_enum.c_str());
}

TEST_F(MacroCheckerTest, jsEvalSyntax)
{
  size_t startOffset = 159;
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->jsSyntaxDef);
  ASSERT_TRUE(checker.IsECaseSyntax(startOffset));
  ASSERT_STREQ(checker.RangeToString(startOffset, checker.GetLastFoundSyntaxOffset()).c_str(), analyzer::checker::MacroChecker::KeyWord_eval.c_str());
}

TEST_F(MacroCheckerTest, jsExportSyntax)
{
  size_t startOffset = 165;
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->jsSyntaxDef);
  ASSERT_TRUE(checker.IsECaseSyntax(startOffset));
  ASSERT_STREQ(checker.RangeToString(startOffset, checker.GetLastFoundSyntaxOffset()).c_str(), analyzer::checker::MacroChecker::KeyWord_export.c_str());
}

TEST_F(MacroCheckerTest, jsExtendsSyntax)
{
  size_t startOffset = 175;
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->jsSyntaxDef);
  ASSERT_TRUE(checker.IsECaseSyntax(startOffset));
  ASSERT_STREQ(checker.RangeToString(startOffset, checker.GetLastFoundSyntaxOffset()).c_str(), analyzer::checker::MacroChecker::KeyWord_extends.c_str());
}

TEST_F(MacroCheckerTest, jsFalseSyntax)
{
  size_t startOffset = 186;
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->jsSyntaxDef);
  ASSERT_TRUE(checker.IsFCaseSyntax(startOffset));
  ASSERT_STREQ(checker.RangeToString(startOffset, checker.GetLastFoundSyntaxOffset()).c_str(), analyzer::checker::MacroChecker::KeyWord_false.c_str());
}

TEST_F(MacroCheckerTest, jsFinalSyntax)
{
  size_t startOffset = 194;
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->jsSyntaxDef);
  ASSERT_TRUE(checker.IsFCaseSyntax(startOffset));
  ASSERT_STREQ(checker.RangeToString(startOffset, checker.GetLastFoundSyntaxOffset()).c_str(), analyzer::checker::MacroChecker::KeyWord_final.c_str());
}

TEST_F(MacroCheckerTest, jsFinallySyntax)
{
  size_t startOffset = 201;
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->jsSyntaxDef);
  ASSERT_TRUE(checker.IsFCaseSyntax(startOffset));
  ASSERT_STREQ(checker.RangeToString(startOffset, checker.GetLastFoundSyntaxOffset()).c_str(), analyzer::checker::MacroChecker::KeyWord_finally.c_str());
}

TEST_F(MacroCheckerTest, jsFloatSyntax)
{
  size_t startOffset = 211;
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->jsSyntaxDef);
  ASSERT_TRUE(checker.IsFCaseSyntax(startOffset));
  ASSERT_STREQ(checker.RangeToString(startOffset, checker.GetLastFoundSyntaxOffset()).c_str(), analyzer::checker::MacroChecker::KeyWord_float.c_str());
}

TEST_F(MacroCheckerTest, jsForSyntax)
{
  size_t startOffset = 219;
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->jsSyntaxDef);
  ASSERT_TRUE(checker.IsFCaseSyntax(startOffset));
  ASSERT_STREQ(checker.RangeToString(startOffset, checker.GetLastFoundSyntaxOffset()).c_str(), analyzer::checker::MacroChecker::KeyWord_for.c_str());
}

TEST_F(MacroCheckerTest, jsFunctionSyntax)
{
  size_t startOffset = 225;
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->jsSyntaxDef);
  ASSERT_TRUE(checker.IsFCaseSyntax(startOffset));
  ASSERT_STREQ(checker.RangeToString(startOffset, checker.GetLastFoundSyntaxOffset()).c_str(), analyzer::checker::MacroChecker::KeyWord_function.c_str());
}

TEST_F(MacroCheckerTest, jsGoToSyntax)
{
  size_t startOffset = 235;
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->jsSyntaxDef);
  ASSERT_TRUE(checker.IsGCaseSyntax(startOffset));
  ASSERT_STREQ(checker.RangeToString(startOffset, checker.GetLastFoundSyntaxOffset()).c_str(), analyzer::checker::MacroChecker::KeyWord_goto.c_str());
}

TEST_F(MacroCheckerTest, jsImplementesSyntax)
{
  size_t startOffset = 247;
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->jsSyntaxDef);
  ASSERT_TRUE(checker.IsICaseSyntax(startOffset));
  ASSERT_STREQ(checker.RangeToString(startOffset, checker.GetLastFoundSyntaxOffset()).c_str(), analyzer::checker::MacroChecker::KeyWord_implements.c_str());
}

TEST_F(MacroCheckerTest, jsImportSyntax)
{
  size_t startOffset = 260;
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->jsSyntaxDef);
  ASSERT_TRUE(checker.IsICaseSyntax(startOffset));
  ASSERT_STREQ(checker.RangeToString(startOffset, checker.GetLastFoundSyntaxOffset()).c_str(), analyzer::checker::MacroChecker::KeyWord_import.c_str());
}

TEST_F(MacroCheckerTest, jsInstanceofSyntax)
{
  size_t startOffset = 274;
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->jsSyntaxDef);
  ASSERT_TRUE(checker.IsICaseSyntax(startOffset));
  ASSERT_STREQ(checker.RangeToString(startOffset, checker.GetLastFoundSyntaxOffset()).c_str(), analyzer::checker::MacroChecker::KeyWord_instanceof.c_str());
}

TEST_F(MacroCheckerTest, jsInterfaceSyntax)
{
  size_t startOffset = 293;
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->jsSyntaxDef);
  ASSERT_TRUE(checker.IsICaseSyntax(startOffset));
  ASSERT_STREQ(checker.RangeToString(startOffset, checker.GetLastFoundSyntaxOffset()).c_str(), analyzer::checker::MacroChecker::KeyWord_interface.c_str());
}

TEST_F(MacroCheckerTest, jsIntSyntax)
{
  size_t startOffset = 287;
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->jsSyntaxDef);
  ASSERT_TRUE(checker.IsICaseSyntax(startOffset));
  ASSERT_STREQ(checker.RangeToString(startOffset, checker.GetLastFoundSyntaxOffset()).c_str(), analyzer::checker::MacroChecker::KeyWord_int.c_str());
}

TEST_F(MacroCheckerTest, jsInSyntax)
{
  size_t startOffset = 269;
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->jsSyntaxDef);
  ASSERT_TRUE(checker.IsICaseSyntax(startOffset));
  ASSERT_STREQ(checker.RangeToString(startOffset, checker.GetLastFoundSyntaxOffset()).c_str(), analyzer::checker::MacroChecker::KeyWord_in.c_str());
}

TEST_F(MacroCheckerTest, jsLetSyntax)
{
  size_t startOffset = 304;
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->jsSyntaxDef);
  ASSERT_TRUE(checker.IsLCaseSyntax(startOffset));
  ASSERT_STREQ(checker.RangeToString(startOffset, checker.GetLastFoundSyntaxOffset()).c_str(), analyzer::checker::MacroChecker::KeyWord_let.c_str());
}
TEST_F(MacroCheckerTest, jsLongSyntax)
{
  size_t startOffset = 311;
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->jsSyntaxDef);
  ASSERT_TRUE(checker.IsLCaseSyntax(startOffset));
  ASSERT_STREQ(checker.RangeToString(startOffset, checker.GetLastFoundSyntaxOffset()).c_str(), analyzer::checker::MacroChecker::KeyWord_long.c_str());
}

TEST_F(MacroCheckerTest, jsNativeSyntax)
{
  size_t startOffset = 318;
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->jsSyntaxDef);
  ASSERT_TRUE(checker.IsNCaseSyntax(startOffset));
  ASSERT_STREQ(checker.RangeToString(startOffset, checker.GetLastFoundSyntaxOffset()).c_str(), analyzer::checker::MacroChecker::KeyWord_native.c_str());
}
TEST_F(MacroCheckerTest, jsNewSyntax)
{
  size_t startOffset = 327;
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->jsSyntaxDef);
  ASSERT_TRUE(checker.IsNCaseSyntax(startOffset));
  ASSERT_STREQ(checker.RangeToString(startOffset, checker.GetLastFoundSyntaxOffset()).c_str(), analyzer::checker::MacroChecker::KeyWord_new.c_str());
}
TEST_F(MacroCheckerTest, jsNullSyntax)
{
  size_t startOffset = 332;
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->jsSyntaxDef);
  ASSERT_TRUE(checker.IsNCaseSyntax(startOffset));
  ASSERT_STREQ(checker.RangeToString(startOffset, checker.GetLastFoundSyntaxOffset()).c_str(), analyzer::checker::MacroChecker::KeyWord_null.c_str());
}

TEST_F(MacroCheckerTest, jsPackageSyntax)
{
  size_t startOffset = 339;
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->jsSyntaxDef);
  ASSERT_TRUE(checker.IsPCaseSyntax(startOffset));
  ASSERT_STREQ(checker.RangeToString(startOffset, checker.GetLastFoundSyntaxOffset()).c_str(), analyzer::checker::MacroChecker::KeyWord_package.c_str());
}

TEST_F(MacroCheckerTest, jsPrivateSyntax)
{
  size_t startOffset = 349;
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->jsSyntaxDef);
  ASSERT_TRUE(checker.IsPCaseSyntax(startOffset));
  ASSERT_STREQ(checker.RangeToString(startOffset, checker.GetLastFoundSyntaxOffset()).c_str(), analyzer::checker::MacroChecker::KeyWord_private.c_str());
}

TEST_F(MacroCheckerTest, jsProtectedSyntax)
{
  size_t startOffset = 359;
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->jsSyntaxDef);
  ASSERT_TRUE(checker.IsPCaseSyntax(startOffset));
  ASSERT_STREQ(checker.RangeToString(startOffset, checker.GetLastFoundSyntaxOffset()).c_str(), analyzer::checker::MacroChecker::KeyWord_protected.c_str());
}

TEST_F(MacroCheckerTest, jsPublicSyntax)
{
  size_t startOffset = 370;
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->jsSyntaxDef);
  ASSERT_TRUE(checker.IsPCaseSyntax(startOffset));
  ASSERT_STREQ(checker.RangeToString(startOffset, checker.GetLastFoundSyntaxOffset()).c_str(), analyzer::checker::MacroChecker::KeyWord_public.c_str());
}

TEST_F(MacroCheckerTest, jsReturnSyntax)
{
  size_t startOffset = 379;
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->jsSyntaxDef);
  ASSERT_TRUE(checker.IsRCaseSyntax(startOffset));
  ASSERT_STREQ(checker.RangeToString(startOffset, checker.GetLastFoundSyntaxOffset()).c_str(), analyzer::checker::MacroChecker::KeyWord_return.c_str());
}

TEST_F(MacroCheckerTest, jsShortSyntax)
{
  size_t startOffset = 388;
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->jsSyntaxDef);
  ASSERT_TRUE(checker.IsSCaseSyntax(startOffset));
  ASSERT_STREQ(checker.RangeToString(startOffset, checker.GetLastFoundSyntaxOffset()).c_str(), analyzer::checker::MacroChecker::KeyWord_short.c_str());
}

TEST_F(MacroCheckerTest, jsStaticSyntax)
{
  size_t startOffset = 396;
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->jsSyntaxDef);
  ASSERT_TRUE(checker.IsSCaseSyntax(startOffset));
  ASSERT_STREQ(checker.RangeToString(startOffset, checker.GetLastFoundSyntaxOffset()).c_str(), analyzer::checker::MacroChecker::KeyWord_static.c_str());
}

TEST_F(MacroCheckerTest, jsSuperSyntax)
{
  size_t startOffset = 404;
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->jsSyntaxDef);
  ASSERT_TRUE(checker.IsSCaseSyntax(startOffset));
  ASSERT_STREQ(checker.RangeToString(startOffset, checker.GetLastFoundSyntaxOffset()).c_str(), analyzer::checker::MacroChecker::KeyWord_super.c_str());
}

TEST_F(MacroCheckerTest, jsSwitchSyntax)
{
  size_t startOffset = 413;
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->jsSyntaxDef);
  ASSERT_TRUE(checker.IsSCaseSyntax(startOffset));
  ASSERT_STREQ(checker.RangeToString(startOffset, checker.GetLastFoundSyntaxOffset()).c_str(), analyzer::checker::MacroChecker::KeyWord_switch.c_str());
}

TEST_F(MacroCheckerTest, jsSyncronizedSyntax)
{
  size_t startOffset = 422;
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->jsSyntaxDef);
  ASSERT_TRUE(checker.IsSCaseSyntax(startOffset));
  ASSERT_STREQ(checker.RangeToString(startOffset, checker.GetLastFoundSyntaxOffset()).c_str(), analyzer::checker::MacroChecker::KeyWord_synchronized.c_str());
}

TEST_F(MacroCheckerTest, jsThisSyntax)
{
  size_t startOffset = 437;
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->jsSyntaxDef);
  ASSERT_TRUE(checker.IsTCaseSyntax(startOffset));
  ASSERT_STREQ(checker.RangeToString(startOffset, checker.GetLastFoundSyntaxOffset()).c_str(), analyzer::checker::MacroChecker::KeyWord_this.c_str());
}
TEST_F(MacroCheckerTest, jsThrowSyntax)
{
  size_t startOffset = 443;
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->jsSyntaxDef);
  ASSERT_TRUE(checker.IsTCaseSyntax(startOffset));
  ASSERT_STREQ(checker.RangeToString(startOffset, checker.GetLastFoundSyntaxOffset()).c_str(), analyzer::checker::MacroChecker::KeyWord_throw.c_str());
}
TEST_F(MacroCheckerTest, jsThrowsSyntax)
{
  size_t startOffset = 451;
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->jsSyntaxDef);
  ASSERT_TRUE(checker.IsTCaseSyntax(startOffset));
  ASSERT_STREQ(checker.RangeToString(startOffset, checker.GetLastFoundSyntaxOffset()).c_str(), analyzer::checker::MacroChecker::KeyWord_throws.c_str());
}
TEST_F(MacroCheckerTest, jsTransientSyntax)
{
  size_t startOffset = 460;
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->jsSyntaxDef);
  ASSERT_TRUE(checker.IsTCaseSyntax(startOffset));
  ASSERT_STREQ(checker.RangeToString(startOffset, checker.GetLastFoundSyntaxOffset()).c_str(), analyzer::checker::MacroChecker::KeyWord_transient.c_str());
}

TEST_F(MacroCheckerTest, jsTrueSyntax)
{
  size_t startOffset = 472;
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->jsSyntaxDef);
  ASSERT_TRUE(checker.IsTCaseSyntax(startOffset));
  ASSERT_STREQ(checker.RangeToString(startOffset, checker.GetLastFoundSyntaxOffset()).c_str(), analyzer::checker::MacroChecker::KeyWord_true.c_str());
}

TEST_F(MacroCheckerTest, jsTrySyntax)
{
  size_t startOffset = 478;
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->jsSyntaxDef);
  ASSERT_TRUE(checker.IsTCaseSyntax(startOffset));
  ASSERT_STREQ(checker.RangeToString(startOffset, checker.GetLastFoundSyntaxOffset()).c_str(), analyzer::checker::MacroChecker::KeyWord_try.c_str());
}

TEST_F(MacroCheckerTest, jsTypeOfSyntax)
{
  size_t startOffset = 484;
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->jsSyntaxDef);
  ASSERT_TRUE(checker.IsTCaseSyntax(startOffset));
  ASSERT_STREQ(checker.RangeToString(startOffset, checker.GetLastFoundSyntaxOffset()).c_str(), analyzer::checker::MacroChecker::KeyWord_typeof.c_str());
}

TEST_F(MacroCheckerTest, jsVarSyntax)
{
  size_t startOffset = 493;
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->jsSyntaxDef);
  ASSERT_TRUE(checker.IsVCaseSyntax(startOffset));
  ASSERT_STREQ(checker.RangeToString(startOffset, checker.GetLastFoundSyntaxOffset()).c_str(), analyzer::checker::MacroChecker::KeyWord_var.c_str());
}

TEST_F(MacroCheckerTest, jsVoidSyntax)
{
  size_t startOffset = 499;
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->jsSyntaxDef);
  ASSERT_TRUE(checker.IsVCaseSyntax(startOffset));
  ASSERT_STREQ(checker.RangeToString(startOffset, checker.GetLastFoundSyntaxOffset()).c_str(), analyzer::checker::MacroChecker::KeyWord_void.c_str());
}

TEST_F(MacroCheckerTest, jsVolatileSyntax)
{
  size_t startOffset = 505;
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->jsSyntaxDef);
  ASSERT_TRUE(checker.IsVCaseSyntax(startOffset));
  ASSERT_STREQ(checker.RangeToString(startOffset, checker.GetLastFoundSyntaxOffset()).c_str(), analyzer::checker::MacroChecker::KeyWord_volatile.c_str());
}

TEST_F(MacroCheckerTest, jsWhileSyntax)
{
  size_t startOffset = 516;
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->jsSyntaxDef);
  ASSERT_TRUE(checker.IsWCaseSyntax(startOffset));
  ASSERT_STREQ(checker.RangeToString(startOffset, checker.GetLastFoundSyntaxOffset()).c_str(), analyzer::checker::MacroChecker::KeyWord_while.c_str());
}
TEST_F(MacroCheckerTest, jsWithSyntax)
{
  size_t startOffset = 524;
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->jsSyntaxDef);
  ASSERT_TRUE(checker.IsWCaseSyntax(startOffset));
  ASSERT_STREQ(checker.RangeToString(startOffset, checker.GetLastFoundSyntaxOffset()).c_str(), analyzer::checker::MacroChecker::KeyWord_with.c_str());
}

TEST_F(MacroCheckerTest, jsYieldSyntax)
{
  size_t startOffset = 531;
  analyzer::checker::MacroChecker checker;
  checker.SetData(this->jsSyntaxDef);
  ASSERT_TRUE(checker.IsYCaseSyntax(startOffset));
  ASSERT_STREQ(checker.RangeToString(startOffset, checker.GetLastFoundSyntaxOffset()).c_str(), analyzer::checker::MacroChecker::KeyWord_yield.c_str());
}
#endif
