/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef FILETEST_H
#define FILETEST_H

#include <gtest\gtest.h>

#include <vector>
#include <string>
#include <memory>

#include "AnalyzerLib\core\File.h"

class FileTest : public testing::Test
{
public:
  FileTest()
    : file1(), charVector(), fileName1("test.txt"), xmlHeader()
  {}
  virtual ~FileTest(){
  }

  void SetUp(){
    for (int i = 0; i < 4; i++){
      this->charVector.push_back('a');
    }

    this->xmlHeader = std::vector<unsigned char>{ '<', '?', 'x', 'm', 'l', ' ', 'v', 'e', 'r', 's', 'i', 'o', 'n', '=', '"', '1', '.', '0', '"', ' ', 'e', 'n', 'c', 'o', 'd', 'i', 'n', 'g', '=', '"', 'u', 't', 'f', '-', '8', '"', '?', '>' };
  }

  analyzer::core::File file1;
  std::vector<unsigned char> charVector;
  std::string fileName1;
  std::vector<unsigned char> xmlHeader;
};

TEST_F(FileTest, Init)
{
  ASSERT_FALSE(file1.IsLoaded());
}

TEST_F(FileTest, InitWithData)
{
  analyzer::core::File file(fileName1, charVector);
  ASSERT_TRUE(file.IsLoaded());
}

TEST_F(FileTest, SetFileData)
{
  this->file1.SetFileData(fileName1, charVector);

  ASSERT_STREQ(this->file1.GetFileName().c_str(), this->fileName1.c_str());
  ASSERT_EQ(this->file1.GetSize(), charVector.size());
}

TEST_F(FileTest, SetFileNameWithPath)
{
  std::string fileName("testDir/subTestDir/test.txt");
  this->file1.SetFileData(fileName, charVector);

  ASSERT_STREQ(this->file1.GetPath()[0].c_str(), "testDir");
  ASSERT_STREQ(this->file1.GetPath()[1].c_str(), "subTestDir");
}

TEST_F(FileTest, CpyCtor)
{
  this->file1.SetFileData(fileName1, charVector);

  analyzer::core::File theNewfile(this->file1);

  ASSERT_STREQ(theNewfile.GetFileName().c_str(), this->fileName1.c_str());
  ASSERT_EQ(theNewfile.GetSize(), this->charVector.size());
}

TEST_F(FileTest, AssignOperator)
{
  analyzer::core::File theNewfile;
  {
    this->file1.SetFileData(fileName1, charVector);
    theNewfile = this->file1;
  }
  ASSERT_STREQ(theNewfile.GetFileName().c_str(), this->fileName1.c_str());
  ASSERT_EQ(theNewfile.GetSize(), this->charVector.size());
}

TEST_F(FileTest, UseRichTextEmpty)
{
  ASSERT_FALSE(this->file1.UseRichText());
}

TEST_F(FileTest, UseRichTextBMP)
{
  std::wstring testFilesDirW(TestSupport::GetInstance()->GetTestFilesDir());
  std::string testFile(testFilesDirW.begin(), testFilesDirW.end());
  std::string bmpFile("bmp/test16_1.bmp");
  testFile += "/" + bmpFile;
  auto dataPtr = TestSupport::GetInstance()->GetDataFromTestFilesDir(bmpFile);
  std::vector<unsigned char> data(dataPtr->begin(), dataPtr->end());

  this->file1.SetFileData(testFile, data);
  ASSERT_TRUE(this->file1.UseRichText());
}

TEST_F(FileTest, getText)
{
  std::wstring testFilesDirW(TestSupport::GetInstance()->GetTestFilesDir());
  std::string testFile(testFilesDirW.begin(), testFilesDirW.end());
  std::string bmpFile("bmp/test16_1.bmp");
  testFile += "/" + bmpFile;
  auto dataPtr = TestSupport::GetInstance()->GetDataFromTestFilesDir(bmpFile);
  std::vector<unsigned char> data(dataPtr->begin(), dataPtr->end());
  this->file1.SetFileData(testFile, data);
  std::string text(this->file1.GetText());
  std::string compTxt("<!DOCTYPE html><html><head><title>Windows Bitmap</title></head>");
  std::string testTxt(text.substr(0, 63));
  ASSERT_STREQ(compTxt.c_str(), testTxt.c_str());
}
#endif