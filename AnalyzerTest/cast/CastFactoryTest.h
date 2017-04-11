#ifndef CASTFACTORYTEST_H
#define CASTFACTORYTEST_H

#include <gtest/gtest.h>

#include "AnalyzerLib/cast/Cast.h"
#include "AnalyzerLib/cast/EmptyCast.h"
#include "AnalyzerLib/cast/CastFactory.h"
#include "AnalyzerLib/cast/SingleByteCast.h"

class CastFactoryTest : public testing::Test
{
public:
  CastFactoryTest() : testing::Test(), data(new std::vector<unsigned char>()){}
  virtual ~CastFactoryTest() {}

  std::shared_ptr<std::vector<unsigned char>> data;
};

TEST_F(CastFactoryTest, emptyByte)
{
  std::shared_ptr<analyzer::cast::Cast> cast(analyzer::cast::CastFactory::CreateCast(this->data));
  bool isEmptyCast = false;
  if (dynamic_cast<analyzer::cast::EmptyCast*>(cast.get())) {
    isEmptyCast = true;
  }
  ASSERT_TRUE(isEmptyCast);
}

TEST_F(CastFactoryTest, singleByteCast)
{
  this->data->push_back(static_cast<unsigned short>(0));
  std::shared_ptr<analyzer::cast::Cast> cast(analyzer::cast::CastFactory::CreateCast(this->data));
  bool isSingleByteCast = false;
  if (dynamic_cast<analyzer::cast::SingleByteCast*>(cast.get())) {
    isSingleByteCast = true;
  }
  ASSERT_TRUE(isSingleByteCast);
}
#endif