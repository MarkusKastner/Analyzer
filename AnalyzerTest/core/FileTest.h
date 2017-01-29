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
#include "AnalyzerLib\interpreter\TextStyleInterpreter.h"
#include "AnalyzerLib\interpreter\BinaryStyleInterpreter.h"

class FileTest : public testing::Test
{
public:
  FileTest()
    : file1(), charVector(), fileName1("test.txt"), xmlHeader(nullptr)
  {}
  virtual ~FileTest(){
    if (this->xmlHeader != nullptr) {
      delete this->xmlHeader;
    }
  }

  void SetUp(){
    for (int i = 0; i < 4; i++){
      this->charVector.push_back('a');
    }

    this->xmlHeader = new std::vector<char>{ '<', '?', 'x', 'm', 'l', ' ', 'v', 'e', 'r', 's', 'i', 'o', 'n', '=', '"', '1', '.', '0', '"', ' ', 'e', 'n', 'c', 'o', 'd', 'i', 'n', 'g', '=', '"', 'u', 't', 'f', '-', '8', '"', '?', '>' };
  }

  analyzer::core::File file1;
  std::vector<char> charVector;
  std::string fileName1;
  std::vector<char> * xmlHeader;
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

TEST_F(FileTest, GetText)
{
  this->file1.SetFileData(fileName1, charVector);
  this->file1.SetDisplayOptions(analyzer::base::BaseFormat::text, analyzer::base::DetailFormat::simpleText);
  ASSERT_STREQ(this->file1.GetText().get()->c_str(), L"aaaa");
}

TEST_F(FileTest, ChangeDisplayOptions)
{
  this->file1.SetFileData(fileName1, charVector);
  this->file1.SetDisplayOptions(analyzer::base::BaseFormat::text, analyzer::base::DetailFormat::simpleText);
  ASSERT_STREQ(this->file1.GetText()->c_str(), L"aaaa");
  this->file1.SetDisplayOptions(analyzer::base::BaseFormat::binary, analyzer::base::DetailFormat::bits);
  ASSERT_STREQ(this->file1.GetText()->c_str(), L"01100001  01100001  01100001  01100001    [097][097][097][097]");
}

TEST_F(FileTest, BinaryInterpreterOptions)
{
  this->file1.SetFileData(fileName1, charVector);
  ASSERT_EQ(this->file1.GetBinaryInterpreterOptions()[0], analyzer::base::DetailFormat::bits);
  ASSERT_EQ(this->file1.GetBinaryInterpreterOptions()[1], analyzer::base::DetailFormat::hex);
}

TEST_F(FileTest, TextInterpreterOptions)
{
  this->file1.SetFileData(fileName1, charVector);
  ASSERT_EQ(this->file1.GetTextInterpreterOptions()[0], analyzer::base::DetailFormat::simpleText);
}

TEST_F(FileTest, xmlRecognition)
{
  this->file1.SetFileData("someXML.xml", *this->xmlHeader);
  ASSERT_EQ(this->file1.GetTextInterpreterOptions()[1], analyzer::base::DetailFormat::xml);
}

#endif