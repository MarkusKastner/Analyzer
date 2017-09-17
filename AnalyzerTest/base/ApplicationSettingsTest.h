/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef APPLICATIONSETTINGSTEST_H
#define APPLICATIONSETTINGSTEST_H

#include <gtest\gtest.h>
#include "TestSupport.h"

#include "AnalyzerLib\base\ApplicationSettings.h"
#include "AnalyzerLib\base\error\AnalyzerBaseException.h"

class ApplicationSettingsTest : public testing::Test
{
public:
  ApplicationSettingsTest()
  :testing::Test(), applicationSettings()
  {}

  virtual ~ApplicationSettingsTest() {}

  virtual void SetUp() {

  }

  analyzer::base::ApplicationSettings applicationSettings;
};

TEST_F(ApplicationSettingsTest, init)
{
  analyzer::base::ApplicationSettings appSettings;
}

TEST_F(ApplicationSettingsTest, appPath)
{
  this->applicationSettings.SetAppDir(TestSupport::GetInstance()->GetAppdir());
  ASSERT_STREQ(TestSupport::GetInstance()->GetAppdir().c_str(), this->applicationSettings.GetAppDir().c_str());
}

TEST_F(ApplicationSettingsTest, appPathNotSet)
{
  analyzer::base::AnalyzerBaseException::ErrorCode errCode = analyzer::base::AnalyzerBaseException::ErrorCode::Empty;
  try {
    this->applicationSettings.GetAppDir();
  }
  catch (analyzer::base::AnalyzerBaseException & ex)
  {
    errCode = ex.GetErrorCode();
  }
  ASSERT_EQ(errCode, analyzer::base::AnalyzerBaseException::ErrorCode::ApplicationPathNotSet);
}

#endif