/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef JSFCASECHECKERTEST_H
#define JSFCASECHECKERTEST_H

#include <gtest/gtest.h>
#include "TestSupport.h"

#include "AnalyzerLib/contentchecker/javascript/JSFCaseChecker.h"
#include "AnalyzerLib/contentchecker/SyntaxCheckerParent.h"

class JSFCaseCheckerTest : public testing::Test
{
public:
  class Parent : public analyzer::checker::SyntaxCheckerParent
  {
  public:
    Parent() 
      :analyzer::checker::SyntaxCheckerParent(), 
      lastFoundSyntaxOffset(0), data(new std::vector<unsigned char>()){
    }

    virtual ~Parent() {
    }

    virtual void SetLastFoundSyntaxOffset(const size_t & offset) {
      this->lastFoundSyntaxOffset = offset;
    }

    const size_t & GetLastFoundSyntaxOffset() const {
      return this->lastFoundSyntaxOffset;
    }

    void SetData(const std::shared_ptr<std::vector<unsigned char>> & data) {
      this->data = data;
    }

    virtual const std::shared_ptr<std::vector<unsigned char>> & GetData() const {
      return this->data;
    }

  private:
    size_t lastFoundSyntaxOffset;
    std::shared_ptr<std::vector<unsigned char>> data;
  };

  JSFCaseCheckerTest()
    : testing::Test(), parent()
  {
  }
  Parent parent;
};

TEST_F(JSFCaseCheckerTest, data)
{
  std::shared_ptr<std::vector<unsigned char>> data(new std::vector<unsigned char>());
  data->push_back('x');
  this->parent.SetData(data);

  analyzer::checker::JSFCaseChecker jsICaseChecker(&this->parent);
  ASSERT_TRUE(jsICaseChecker.HasData());

  jsICaseChecker.ReleaseData();
  ASSERT_FALSE(jsICaseChecker.HasData());

  jsICaseChecker.SetData(data);
  ASSERT_TRUE(jsICaseChecker.HasData());

}

TEST_F(JSFCaseCheckerTest, forCase)
{
  this->parent.SetData(TestSupport::GetInstance()->GetDataFromTestFilesDir("JavascriptSyntax/for.txt"));
  analyzer::checker::JSFCaseChecker jsFCaseChecker(&this->parent);

  size_t offset = 2;
  ASSERT_FALSE(jsFCaseChecker.IsMyCase(offset));
  offset = 12;
  ASSERT_FALSE(jsFCaseChecker.IsMyCase(offset));

  offset = 22;
  ASSERT_TRUE(jsFCaseChecker.IsMyCase(offset));
  ASSERT_EQ(this->parent.GetLastFoundSyntaxOffset(), analyzer::checker::JSFCaseChecker::KeyWord_for.size());

  offset = 32;
  ASSERT_TRUE(jsFCaseChecker.IsMyCase(offset));
  offset = 42;
  ASSERT_TRUE(jsFCaseChecker.IsMyCase(offset));
}
#endif