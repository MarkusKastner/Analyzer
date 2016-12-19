#ifndef ANALYZERBASETEST_H
#define ANALYZERBASETEST_H

#include <gtest\gtest.h>

#include "AnalyzerLib\base\AnalyzerBase.h"
#include "AnalyzerLib\base\AnalyzerBaseObserver.h"
#include "AnalyzerLib\base\error\AnalyzerBaseException.h"
#include "AnalyzerLib\core\File.h"

class AnalyzerBaseTest : public testing::Test
{
public:

  class SomeObserver : public analyzer::base::AnalyzerBaseObserver
  {
  public:
    SomeObserver()
      :interpreterChanged(false), filesChanged(false)
    {}
    ~SomeObserver(){}

    virtual void NotifyInterprterChange(){
      this->interpreterChanged = true;
    }
    virtual void NotifyFileChange(){
      this->filesChanged = true;
    }
    bool InterpreterChanged(){
      return this->interpreterChanged;
    }
    bool FilesChanged(){
      return this->filesChanged;
    }
  private:
    bool interpreterChanged;
    bool filesChanged;
  };

  AnalyzerBaseTest()
    :analyzerBase1(), observer1(), path1("c:/dev/test.txt"), dummyData1(), path2("c:/dev/test.zip"), path3("c:/dev/test.docx")
  {}
  ~AnalyzerBaseTest(){}

  void SetUp(){
    dummyData1.push_back('D');
    dummyData1.push_back('u');
    dummyData1.push_back('m');
    dummyData1.push_back('m');
    dummyData1.push_back('y');

    analyzerFile.SetFileData(path1, dummyData1);
  }

  analyzer::base::AnalyzerBase analyzerBase1;
  SomeObserver observer1;
  std::string path1;
  std::vector<char> dummyData1;
  analyzer::core::File analyzerFile;
  std::string path2;
  std::string path3;
};

TEST_F(AnalyzerBaseTest, init)
{
  ASSERT_FALSE(analyzerBase1.HasActivefile());
}

//
//TEST_F(AnalyzerBaseTest, SwitchMode)
//{
//  this->analyzerBase1.SetTextMode();
//  ASSERT_TRUE(dynamic_cast<analyzer::interpreter::TextStyleInterpreter*>(this->analyzerBase1.Interpreter()));
//  this->analyzerBase1.SetBinaryMode();
//  ASSERT_TRUE(dynamic_cast<analyzer::interpreter::BinaryStyleInterpreter*>(this->analyzerBase1.Interpreter()));
//}
//
//TEST_F(AnalyzerBaseTest, SwitchModeWithData)
//{
//  ASSERT_FALSE(this->analyzerBase1.HasData());
//
//  this->analyzerBase1.Interpreter()->ResetData(this->dummyData1);
//  this->analyzerBase1.SetTextMode();
//  ASSERT_TRUE(this->analyzerBase1.HasData());
//  this->analyzerBase1.SetBinaryMode();
//  ASSERT_TRUE(this->analyzerBase1.HasData());
//}

TEST_F(AnalyzerBaseTest, HasObserver)
{
  ASSERT_EQ(this->analyzerBase1.NumberOfObservers(), 0);
}

TEST_F(AnalyzerBaseTest, RegisterObserver)
{
  this->analyzerBase1.RegisterObserver(&this->observer1);
  ASSERT_EQ(this->analyzerBase1.NumberOfObservers(), 1);
}

TEST_F(AnalyzerBaseTest, RegisterObserverTwice)
{
  this->analyzerBase1.RegisterObserver(&this->observer1);
  this->analyzerBase1.RegisterObserver(&this->observer1);
  ASSERT_EQ(this->analyzerBase1.NumberOfObservers(), 1);
}

TEST_F(AnalyzerBaseTest, UnregisterObserver)
{
  this->analyzerBase1.RegisterObserver(&this->observer1);
  ASSERT_EQ(this->analyzerBase1.NumberOfObservers(), 1);
  this->analyzerBase1.UnregisterObserver(&this->observer1);
  ASSERT_EQ(this->analyzerBase1.NumberOfObservers(), 0);
}

TEST_F(AnalyzerBaseTest, InvalidObserver)
{
  std::string message;
  try{
    this->analyzerBase1.RegisterObserver(nullptr);
  }
  catch (analyzer::base::AnalyzerBaseException & ex){
    message = ex.what();
  }
  ASSERT_STREQ(message.c_str(), "Invalid base observer");
}

TEST_F(AnalyzerBaseTest, EmptyHasData)
{
  ASSERT_FALSE(this->analyzerBase1.HasData());
}

TEST_F(AnalyzerBaseTest, LoadTxtFile)
{
  this->analyzerBase1.RegisterObserver(&this->observer1);
  this->analyzerBase1.LoadFile(this->path1);
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  ASSERT_TRUE(this->analyzerBase1.HasData());
  ASSERT_TRUE(this->observer1.FilesChanged());
}

TEST_F(AnalyzerBaseTest, InvalidFile)
{
  std::string message;
  std::string invalidPath("C:/dev/invalid.txt");
  try{
    this->analyzerBase1.LoadFile(invalidPath);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    this->analyzerBase1.Rethrow();
  }
  catch (analyzer::base::AnalyzerBaseException & ex){
    message = ex.what();
  }
  ASSERT_STREQ(message.c_str(), std::string("Cannot open " + invalidPath).c_str());
}

TEST_F(AnalyzerBaseTest, HasFiles)
{
  ASSERT_FALSE(this->analyzerBase1.HasFiles());
}

TEST_F(AnalyzerBaseTest, AddFile)
{
  this->analyzerBase1.AddAnalyzerFile(this->analyzerFile);
  ASSERT_TRUE(this->analyzerBase1.HasFiles());
}

TEST_F(AnalyzerBaseTest, SetFileAsDefault)
{
  this->analyzerBase1.AddAnalyzerFile(this->analyzerFile);
  ASSERT_STREQ(this->analyzerBase1.GetActiveAnalyzerFile().GetFileName().c_str(), this->analyzerFile.GetFileName().c_str());
}

TEST_F(AnalyzerBaseTest, GetInterpreter)
{
  this->analyzerBase1.AddAnalyzerFile(this->analyzerFile);
  ASSERT_TRUE(analyzerBase1.CurrentInterpreter() != nullptr);
}

TEST_F(AnalyzerBaseTest, FileCount)
{
  this->analyzerBase1.AddAnalyzerFile(this->analyzerFile);
  ASSERT_EQ(this->analyzerBase1.FileCount(), 1);
}

TEST_F(AnalyzerBaseTest, AddFileTwice)
{
  this->analyzerBase1.AddAnalyzerFile(this->analyzerFile);
  this->analyzerBase1.AddAnalyzerFile(this->analyzerFile);
  ASSERT_EQ(this->analyzerBase1.FileCount(), 1);
}

TEST_F(AnalyzerBaseTest, GetFileByName)
{
  this->analyzerBase1.AddAnalyzerFile(this->analyzerFile);
  analyzer::core::File file = this->analyzerBase1.GetAnalyzerFile(path1);
  ASSERT_STREQ(file.GetFileName().c_str(), path1.c_str());
}

TEST_F(AnalyzerBaseTest, TryGetInvalidFileByName)
{
  std::string message;
  try{
    this->analyzerBase1.AddAnalyzerFile(this->analyzerFile);
    analyzer::core::File file = this->analyzerBase1.GetAnalyzerFile("some/invalid/path.txt");
  }
  catch (analyzer::base::AnalyzerBaseException & ex){
    message = ex.what();
  }
  catch (...){

  }
  ASSERT_STREQ(message.c_str(), "unknown file");
}

TEST_F(AnalyzerBaseTest, HasFile)
{
  this->analyzerBase1.AddAnalyzerFile(this->analyzerFile);
  ASSERT_TRUE(this->analyzerBase1.HasFile(this->path1));
}

TEST_F(AnalyzerBaseTest, GetFileByIndex)
{
  this->analyzerBase1.AddAnalyzerFile(this->analyzerFile);
  analyzer::core::File file = this->analyzerBase1.GetAnalyzerFile(0);
  ASSERT_STREQ(file.GetFileName().c_str(), path1.c_str());
}

TEST_F(AnalyzerBaseTest, InvalidfileIndex)
{
  std::string message;
  try{
    this->analyzerBase1.AddAnalyzerFile(this->analyzerFile);
    analyzer::core::File file = this->analyzerBase1.GetAnalyzerFile(1);
  }
  catch (analyzer::base::AnalyzerBaseException & ex){
    message = ex.what();
  }
  catch (...){

  }
  ASSERT_STREQ(message.c_str(), "invalid index");
}

TEST_F(AnalyzerBaseTest, LoadZipFile)
{
  this->analyzerBase1.RegisterObserver(&this->observer1);
  this->analyzerBase1.LoadFile(this->path2);
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  ASSERT_EQ(this->analyzerBase1.FileCount(), 2);
}

TEST_F(AnalyzerBaseTest, LoadDocxFile)
{
  this->analyzerBase1.RegisterObserver(&this->observer1);
  this->analyzerBase1.LoadFile(this->path3);
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  ASSERT_EQ(this->analyzerBase1.FileCount(), 11);
}

TEST_F(AnalyzerBaseTest, GetFileNames)
{
  this->analyzerBase1.RegisterObserver(&this->observer1);
  this->analyzerBase1.LoadFile(this->path2);
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  std::vector<std::string> fileNames(this->analyzerBase1.GetFileNames());
  ASSERT_STREQ(fileNames.at(0).c_str(), "Erlkoenig.txt");
}

TEST_F(AnalyzerBaseTest, SetActiveAnalyzerFile)
{
  this->analyzerBase1.LoadFile(this->path2);
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  std::string defaultActive(this->analyzerBase1.GetActiveAnalyzerFile().GetFileName());
  this->analyzerBase1.RegisterObserver(&this->observer1);
  this->analyzerBase1.SetActiveFile("Zauberlehrling.txt");
  ASSERT_STRNE(defaultActive.c_str(), this->analyzerBase1.GetActiveAnalyzerFile().GetFileName().c_str());
  ASSERT_TRUE(this->observer1.InterpreterChanged());
}

//TEST_F(AnalyzerBaseTest, NotifyInterpreterChanged)
//{
//  this->analyzerBase1.RegisterObserver(&this->observer1);
//  this->analyzerBase1.SetTextMode();
//  ASSERT_TRUE(this->observer1.InterpreterChanged());
//}

#endif