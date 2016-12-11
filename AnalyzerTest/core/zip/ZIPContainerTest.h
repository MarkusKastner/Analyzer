#ifndef ZIPCONTAINERTEST_H
#define ZIPCONTAINERTEST_H

#include <gtest/gtest.h>

#include <string>

#include "AnalyzerLib\core\zip\ZIPContainer.h"

class ZIPContainerTest : public testing::Test
{
public:
  ZIPContainerTest()
    : zipContainer1(),
    testFile1("c:/dev/test.zip")
  {}

  ~ZIPContainerTest()
  {
  }

  void SetUp(){
  }

  analyzer::core::ZIPContainer zipContainer1;
  std::string testFile1;
};

TEST_F(ZIPContainerTest, EmptyOnDefaultInit)
{
  ASSERT_FALSE(zipContainer1.HasContent());
}

TEST_F(ZIPContainerTest, Open)
{
  zipContainer1.Open(testFile1);
  ASSERT_TRUE(zipContainer1.HasContent());
}

#endif