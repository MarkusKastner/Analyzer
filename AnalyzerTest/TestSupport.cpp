/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "TestSupport.h"

#include <filesystem>

namespace fs = std::tr2::sys;

TestSupport::TestSupport()
  :testDir(), testFilesDir()
{

}

TestSupport::~TestSupport()
{

}

void TestSupport::Initialize(const std::string & appPath)
{
  if (nullptr == TestSupport::instance) {
    TestSupport::instance = new TestSupport();
    instance->setup(appPath);
  }
}

TestSupport * TestSupport::GetInstance()
{
  if (nullptr == TestSupport::instance) {
    throw std::exception("Test support not initialized");
  }
  return instance;
}

const std::wstring & TestSupport::GetTestDir() const
{
  return this->testDir;
}

const std::wstring & TestSupport::GetTestFilesDir() const
{
  return this->testFilesDir;
}

TestSupport * TestSupport::instance = nullptr;

void TestSupport::setup(const std::string & appPath)
{
  std::string pathName(appPath.substr(0, appPath.find_last_of('.')));
  fs::path dir(pathName);

  if (!fs::exists(dir)) {
    fs::create_directory(dir);
  }
  this->testDir = dir;
  this->testFilesDir = L"C:/dev/Analyzer/AnalyzerTest/testFiles";
}