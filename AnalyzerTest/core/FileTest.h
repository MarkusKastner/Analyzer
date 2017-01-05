#ifndef FILETEST_H
#define FILETEST_H

#include <gtest\gtest.h>

#include <vector>
#include <string>
#include <memory>

#include "AnalyzerLib\core\File.h"
#include "AnalyzerLib\core\ByteCollection.h"
#include "AnalyzerLib\interpreter\TextStyleInterpreter.h"
#include "AnalyzerLib\interpreter\BinaryStyleInterpreter.h"

class FileTest : public testing::Test
{
public:
  FileTest()
    : file1(), charVector(), fileName1("test.txt"), byteCollection1()
  {}
  virtual ~FileTest(){}

  void SetUp(){
    for (int i = 0; i < 5; i++){
      this->charVector.push_back('a');
    }

    byteCollection1.reset(new analyzer::core::ByteCollection(this->charVector));
  }

  analyzer::core::File file1;
  std::vector<char> charVector;
  std::string fileName1;
  std::shared_ptr<analyzer::core::ByteCollection> byteCollection1;
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
  ASSERT_EQ(this->file1.GetData()->GetSize(), this->byteCollection1->GetSize());
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
  ASSERT_EQ(theNewfile.GetData()->GetSize(), this->byteCollection1->GetSize());
}

TEST_F(FileTest, AssignOperator)
{
  analyzer::core::File theNewfile;
  {
    this->file1.SetFileData(fileName1, charVector);
    theNewfile = this->file1;
  }
  ASSERT_STREQ(theNewfile.GetFileName().c_str(), this->fileName1.c_str());
  ASSERT_EQ(theNewfile.GetData()->GetSize(), this->byteCollection1->GetSize());
}

TEST_F(FileTest, GetInterpreter)
{
  analyzer::core::File file(fileName1, charVector);
  ASSERT_TRUE(file.GetInterpreter()->HasData());
}

TEST_F(FileTest, GetBinaryInterpreter)
{
  analyzer::core::File file(fileName1, charVector);
  ASSERT_TRUE(dynamic_cast<analyzer::interpreter::BinaryStyleInterpreter*>(file.GetBinaryInterpreter().get()));
}

#endif