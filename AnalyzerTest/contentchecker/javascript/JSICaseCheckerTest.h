/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef JSICASECHECKERTEST_H
#define JSICASECHECKERTEST_H

#include <gtest/gtest.h>
#include "TestSupport.h"

#include "AnalyzerLib/contentchecker/javascript/JSICaseChecker.h"
#include "AnalyzerLib/contentchecker/SyntaxCheckerParent.h"

class JSICaseCheckerTest : public testing::Test
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

  JSICaseCheckerTest()
    : testing::Test(), parent()
  {
  }
  Parent parent;
};

TEST_F(JSICaseCheckerTest, data)
{
  std::shared_ptr<std::vector<unsigned char>> data(new std::vector<unsigned char>());
  data->push_back('x');
  this->parent.SetData(data);

  analyzer::checker::JSICaseChecker jsICaseChecker(&this->parent);
  ASSERT_TRUE(jsICaseChecker.HasData());

  jsICaseChecker.ReleaseData();
  ASSERT_FALSE(jsICaseChecker.HasData());

  jsICaseChecker.SetData(data);
  ASSERT_TRUE(jsICaseChecker.HasData());

}

TEST_F(JSICaseCheckerTest, ifCase)
{
  this->parent.SetData(TestSupport::GetInstance()->GetDataFromTestFilesDir("JavascriptSyntax/if.txt"));
  size_t offset = 20;
  analyzer::checker::JSICaseChecker jsICaseChecker(&this->parent);
  ASSERT_TRUE(jsICaseChecker.IsMyCase(offset));
  ASSERT_EQ(this->parent.GetLastFoundSyntaxOffset(), 2);
}

TEST_F(JSICaseCheckerTest, noIFCase1)
{
  this->parent.SetData(TestSupport::GetInstance()->GetDataFromTestFilesDir("JavascriptSyntax/if.txt"));
  size_t offset = 2;
  analyzer::checker::JSICaseChecker jsICaseChecker(&this->parent);
  ASSERT_FALSE(jsICaseChecker.IsMyCase(offset));

  offset = 11;
  ASSERT_FALSE(jsICaseChecker.IsMyCase(offset));
}

#endif