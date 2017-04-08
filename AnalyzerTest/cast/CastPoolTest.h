#ifndef CASTPOOLTEST_H
#define CASTPOOLTEST_H

#include <gtest\gtest.h>

#include "AnalyzerLib/cast/Cast.h"
#include "AnalyzerLib/cast/EmptyCast.h"
#include "AnalyzerLib/cast/CastPool.h"

class CastPoolTest : public testing::Test
{
public:
  CastPoolTest() : testing::Test() {}
  virtual ~CastPoolTest() {}
};

TEST_F(CastPoolTest, singleByte) 
{
  std::vector<unsigned char> data;
  std::shared_ptr<analyzer::cast::Cast> cast(analyzer::cast::CastPool::GetCaster(data));
  bool isEmptyCast = false;
  if (dynamic_cast<analyzer::cast::EmptyCast*>(cast.get())) {
    isEmptyCast = true;
  }
  ASSERT_TRUE(isEmptyCast);
}
#endif