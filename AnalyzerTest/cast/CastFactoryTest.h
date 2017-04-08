#ifndef CASTFACTORYTEST_H
#define CASTFACTORYTEST_H

#include <gtest/gtest.h>

#include "AnalyzerLib/cast/Cast.h"
#include "AnalyzerLib/cast/EmptyCast.h"
#include "AnalyzerLib/cast/CastFactory.h"

class CastFactoryTest : public testing::Test
{
public:
  CastFactoryTest() : testing::Test() {}
  virtual ~CastFactoryTest() {}
};

TEST_F(CastFactoryTest, singleByte)
{
  std::vector<unsigned char> data;
  std::shared_ptr<analyzer::cast::Cast> cast(analyzer::cast::CastFactory::CreateCast(data));
  bool isEmptyCast = false;
  if (dynamic_cast<analyzer::cast::EmptyCast*>(cast.get())) {
    isEmptyCast = true;
  }
  ASSERT_TRUE(isEmptyCast);
}
#endif