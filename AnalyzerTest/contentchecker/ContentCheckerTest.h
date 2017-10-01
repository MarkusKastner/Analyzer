/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef CONTENTCHECKERTEST_H
#define CONTENTCHECKERTEST_H

#include <gtest\gtest.h>

#include "AnalyzerLib/contentchecker/ContentChecker.h"
#include "AnalyzerLib/contentchecker/CheckObserver.h"
#include "AnalyzerLib/contentchecker/error/ContentCheckException.h"

class AnyChecker : public analyzer::checker::ContentChecker
{
public:
  AnyChecker()
    :analyzer::checker::ContentChecker()
  {}
  virtual ~AnyChecker(){}

protected:
  virtual void checkData(){
    auto data = this->getData();

    for (size_t i = this->GetStartOffest(); i < this->GetCheckOffest(); ++i) {
      if (!this->IsChecking()) {
        return;
      }
      if ((*data)[i] == 'G') {
        this->notifyMarkedIndex(i);
      }
      this->notifyCurrentIndex(i);
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
  }
};

class Observer : public analyzer::checker::CheckObserver
{
public:
  Observer() 
    :analyzer::checker::CheckObserver(), finishedReported(false), checkedIndexes(), markedIndexes()
  {}
  virtual ~Observer() {}

  bool FinishedReported() {
    return this->finishedReported;
  }

  std::vector<size_t> GetCheckedIndexes() {
    return this->checkedIndexes;
  }

  std::vector<size_t> GetMarkedIndexes() {
    return this->markedIndexes;
  }

  const analyzer::base::AnalyzerRGB & GetMarkingColor() {
    return this->color;
  }

  virtual void NotifyCheckRunFinished(){
    this->finishedReported = true;
  }

  virtual void NotifyCurrentIndex(const size_t & checkIndex) {
    this->checkedIndexes.push_back(checkIndex);
  }

  virtual void NotifyMarkedIndex(const size_t & markedIndex, const analyzer::base::AnalyzerRGB & color) {
    this->markedIndexes.push_back(markedIndex);
    this->color = color;
  }

private:
  bool finishedReported;
  std::vector<size_t> checkedIndexes;
  std::vector<size_t> markedIndexes;
  analyzer::base::AnalyzerRGB color;
};

class ContentCheckerTest : public testing::Test
{
public:
  ContentCheckerTest() 
    : testing::Test(), checker(new AnyChecker()), observer(new Observer()),
    dummyData1(new std::vector<unsigned char>()), rgb()
  {
  }

  void SetUp() {
    for (unsigned char i = 65; i < 127; ++i) {
      dummyData1->push_back(i);
    }
    
    this->rgb.r = 155;
    this->rgb.g = 151;
    this->rgb.b = 99;
  }

  virtual ~ContentCheckerTest()
  {}

  std::shared_ptr<analyzer::checker::ContentChecker> checker;
  std::shared_ptr<analyzer::checker::CheckObserver> observer;
  std::shared_ptr<std::vector<unsigned char>> dummyData1;
  analyzer::base::AnalyzerRGB rgb;
};

TEST_F(ContentCheckerTest, init)
{
  std::shared_ptr<analyzer::checker::ContentChecker> myChecker(new AnyChecker());
  ASSERT_TRUE(myChecker.get() != nullptr);
}

TEST_F(ContentCheckerTest, registerCheckObserver)
{
  ASSERT_EQ(this->checker->GetNumCheckObservers(), 0);
  this->checker->RegisterCheckObserver(this->observer.get());
  ASSERT_EQ(this->checker->GetNumCheckObservers(), 1);
}

TEST_F(ContentCheckerTest, registerCheckObserverTwice)
{
  this->checker->RegisterCheckObserver(this->observer.get());
  this->checker->RegisterCheckObserver(this->observer.get());
  ASSERT_EQ(this->checker->GetNumCheckObservers(), 1);
}

TEST_F(ContentCheckerTest, unregisterCheckObserver)
{
  this->checker->RegisterCheckObserver(this->observer.get());
  ASSERT_EQ(this->checker->GetNumCheckObservers(), 1);
  this->checker->UnregisterCheckObserver(this->observer.get());
  ASSERT_EQ(this->checker->GetNumCheckObservers(), 0);
}

TEST_F(ContentCheckerTest, workingColor)
{
  this->checker->SetWorkingColor(this->rgb);
  auto retRGB = this->checker->GetWorkingColor();

  ASSERT_EQ(retRGB.r, 155);
  ASSERT_EQ(retRGB.g, 151);
  ASSERT_EQ(retRGB.b, 99);
}

TEST_F(ContentCheckerTest, data)
{
  ASSERT_FALSE(this->checker->HasData());
  this->checker->SetData(this->dummyData1);
  ASSERT_TRUE(this->checker->HasData());
}

TEST_F(ContentCheckerTest, releaseData)
{
  this->checker->SetData(this->dummyData1);
  ASSERT_TRUE(this->checker->HasData());
  this->checker->ReleaseData();
  ASSERT_FALSE(this->checker->HasData());
}

TEST_F(ContentCheckerTest, setRange)
{
  this->checker->SetData(this->dummyData1);
  this->checker->SetCheckRange(5, 50);
  ASSERT_EQ(this->checker->GetStartOffest(), 5);
  ASSERT_EQ(this->checker->GetCheckOffest(), 50);
}

TEST_F(ContentCheckerTest, defaultCheckOffset)
{
  ASSERT_EQ(this->checker->GetCheckOffest(), 0);
  this->checker->SetData(this->dummyData1);
  ASSERT_EQ(this->checker->GetCheckOffest(), this->dummyData1->size());
}

TEST_F(ContentCheckerTest, runCheck)
{
  this->checker->SetData(this->dummyData1);
  ASSERT_FALSE(this->checker->IsChecking());
  this->checker->StartCheck();
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
  ASSERT_TRUE(this->checker->IsChecking());
}

TEST_F(ContentCheckerTest, stopCheck)
{
  this->checker->SetData(this->dummyData1);
  this->checker->StartCheck();
  ASSERT_TRUE(this->checker->IsChecking());
  this->checker->StopCheck();
  std::this_thread::sleep_for(std::chrono::milliseconds(120));
  ASSERT_FALSE(this->checker->IsChecking());
}

TEST_F(ContentCheckerTest, errorOnStartCheckWithoutData)
{
  std::string errorTest("Cannot start without data");
  std::string error;
  try {
    this->checker->StartCheck();
  }
  catch (std::exception & ex) {
    error = std::string(ex.what());
  }
  ASSERT_STREQ(errorTest.c_str(), error.c_str());
}

TEST_F(ContentCheckerTest, finished)
{
  this->checker->RegisterCheckObserver(this->observer.get());
  this->checker->SetData(this->dummyData1);
  this->checker->StartCheck();

  std::this_thread::sleep_for(std::chrono::milliseconds(120));
  ASSERT_TRUE(this->checker->IsFinished());
  ASSERT_TRUE(dynamic_cast<Observer*>(this->observer.get())->FinishedReported());
}

TEST_F(ContentCheckerTest, checkedIndexes)
{
  this->checker->RegisterCheckObserver(this->observer.get());
  this->checker->SetData(this->dummyData1);
  this->checker->SetCheckRange(5, 10);
  this->checker->StartCheck();

  while (true) {
    if (this->checker->IsFinished()) {
      break;
    }
  }
  auto checkedIndexes(dynamic_cast<Observer*>(this->observer.get())->GetCheckedIndexes());
  ASSERT_EQ(checkedIndexes.size(), 5);
  ASSERT_EQ(checkedIndexes[0], 5);
  ASSERT_EQ(checkedIndexes[4], 9);
}

TEST_F(ContentCheckerTest, workingMarkings)
{
  this->checker->RegisterCheckObserver(this->observer.get());
  this->checker->SetData(this->dummyData1);
  this->checker->SetCheckRange(5, 10);
  this->checker->SetWorkingColor(this->rgb);
  this->checker->StartCheck();

  while (true) {
    if (this->checker->IsFinished()) {
      break;
    }
  }
  auto markedIndexes(dynamic_cast<Observer*>(this->observer.get())->GetMarkedIndexes());
  auto markingColor(dynamic_cast<Observer*>(this->observer.get())->GetMarkingColor());

  ASSERT_EQ(markedIndexes.size(), 1);
  ASSERT_EQ(markedIndexes[0], 6);
  ASSERT_EQ(markingColor.b, 99);
}
#endif