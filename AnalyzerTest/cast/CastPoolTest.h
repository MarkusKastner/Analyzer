#ifndef CASTPOOLTEST_H
#define CASTPOOLTEST_H

#include <gtest\gtest.h>

#include "AnalyzerLib/cast/Cast.h"
#include "AnalyzerLib/cast/EmptyCast.h"
#include "AnalyzerLib/cast/CastPool.h"

class CastPoolTest : public testing::Test
{
public:
  CastPoolTest() : testing::Test(), data(new std::vector<unsigned char>()) {}
  virtual ~CastPoolTest() {}

  std::shared_ptr<std::vector<unsigned char>> data;
};

TEST_F(CastPoolTest, emptyCast) 
{
  std::shared_ptr<analyzer::cast::Cast> cast(analyzer::cast::CastPool::GetCaster(this->data));
  bool isEmptyCast = false;
  if (dynamic_cast<analyzer::cast::EmptyCast*>(cast.get())) {
    isEmptyCast = true;
  }
  ASSERT_TRUE(isEmptyCast);
}

TEST_F(CastPoolTest, singleByteCast)
{
  this->data->push_back(10);
  std::shared_ptr<analyzer::cast::Cast> cast(analyzer::cast::CastPool::GetCaster(this->data));

  ASSERT_STREQ(cast->AsIntegerExpression().c_str(), "10");
}
#endif