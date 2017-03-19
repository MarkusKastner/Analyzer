/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef ZIPCONTAINERTEST_H
#define ZIPCONTAINERTEST_H

#include <gtest/gtest.h>
#include "TestSupport.h"

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
    std::wstring filesDirW(TestSupport::GetInstance()->GetTestFilesDir());
    std::string filesDir(filesDirW.begin(), filesDirW.end());

    this->testFile1 = std::string(filesDir + std::string("/test.docx"));
    this->testFile2 = std::string(filesDir + std::string("/test.zip"));
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
  ASSERT_EQ(zipContainer1.GetFileCount(), 2);
}

TEST_F(ZIPContainerTest, GetFiles)
{
  zipContainer1.Open(testFile2);
  auto file1 = zipContainer1.GetFileAt(0);
  auto file2 = zipContainer1.GetFileAt(1);
  ASSERT_STREQ(file1->GetFileName().c_str(), "Erlkoenig.txt");
  ASSERT_STREQ(file2->GetFileName().c_str(), "Zauberlehrling.txt");
}

#endif