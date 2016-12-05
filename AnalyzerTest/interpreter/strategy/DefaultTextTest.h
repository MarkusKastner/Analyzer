#ifndef DEFAULTTEXTTEST_H
#define DEFAULTTEXTTEST_H

#include <gtest/gtest.h>
#include <memory>

#include "AnalyzerLib\interpreter\strategy\DefaultPlainTextStrategy.h"
#include "AnalyzerLib\core\Byte.h"

class DefaultTextTest : public testing::Test
{
public:

  DefaultTextTest()
    : data1(), data2(), strategy(), strategy1(), strategy2()
  {
  }

  ~DefaultTextTest()
  {
  }

  void SetUp()
  {
    data1.push_back(std::shared_ptr<analyzer::core::Byte>(new analyzer::core::Byte(0)));
    strategy1.reset(new analyzer::interpreter::strategy::DefaultPlainTextStrategy(data1));

    data2.push_back(std::shared_ptr<analyzer::core::Byte>(new analyzer::core::Byte(0)));
    data2.push_back(std::shared_ptr<analyzer::core::Byte>(new analyzer::core::Byte(1)));
    data2.push_back(std::shared_ptr<analyzer::core::Byte>(new analyzer::core::Byte(2)));
    data2.push_back(std::shared_ptr<analyzer::core::Byte>(new analyzer::core::Byte(3)));
    strategy2.reset(new analyzer::interpreter::strategy::DefaultPlainTextStrategy(data2));
  }

  std::vector<std::shared_ptr<analyzer::core::Byte>> data1;
  std::vector<std::shared_ptr<analyzer::core::Byte>> data2;

  analyzer::interpreter::strategy::DefaultPlainTextStrategy strategy;
  std::unique_ptr<analyzer::interpreter::strategy::DefaultPlainTextStrategy> strategy1;
  std::unique_ptr<analyzer::interpreter::strategy::DefaultPlainTextStrategy> strategy2;
};

TEST_F(DefaultTextTest, init)
{
  ASSERT_STREQ(strategy.GetPlainText().c_str(), std::string("").c_str());
}

TEST_F(DefaultTextTest, initByte)
{
  ASSERT_STREQ(strategy1->GetPlainText().c_str(), std::string("0").c_str());
}

TEST_F(DefaultTextTest, initByts)
{
  ASSERT_STREQ(strategy2->GetPlainText().c_str(), std::string("0123").c_str());
}

#endif