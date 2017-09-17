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

class ApplicationSettingsTest : public testing::Test
{
public:
  ApplicationSettingsTest()
  :testing::Test()
  {}

  virtual ~ApplicationSettingsTest() {}
};

TEST_F(ApplicationSettingsTest, init)
{
  analyzer::base::ApplicationSettings appSettings;
}

#endif