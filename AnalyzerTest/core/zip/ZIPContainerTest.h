#ifndef ZIPCONTAINERTEST_H
#define ZIPCONTAINERTEST_H

#include <gtest/gtest.h>

#include <string>

#include "AnalyzerLib\core\zip\ZIPContainer.h"
#include "AnalyzerLib\core\File.h"

class ZIPContainerTest : public testing::Test
{
public:
  ZIPContainerTest()
    : zipContainer1(),
    testFile1("c:/dev/test.docx"), testFile2("c:/dev/test.zip")
  {}

  ~ZIPContainerTest()
  {
  }

  void SetUp(){
  }

  analyzer::core::ZIPContainer zipContainer1;
  std::string testFile1;
  std::string testFile2;
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

TEST_F(ZIPContainerTest, FileCount)
{
  zipContainer1.Open(testFile2);
  ASSERT_TRUE(zipContainer1.GetFileCount(), 2);
}

TEST_F(ZIPContainerTest, GetFiles)
{
  zipContainer1.Open(testFile2);
  analyzer::core::File file1 = zipContainer1.GetFileAt(0);
  analyzer::core::File file2 = zipContainer1.GetFileAt(1);
  ASSERT_STREQ(file1.GetFileName().c_str(), "Erlkoenig.txt");
  ASSERT_STREQ(file2.GetFileName().c_str(), "Zauberlehrling.txt");
}

#endif