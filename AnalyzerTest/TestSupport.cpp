/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "TestSupport.h"

#include <filesystem>
#include <fstream>
#include <exception>

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

const std::string & TestSupport::GetTestDir() const
{
  return this->testDir;
}

const std::string & TestSupport::GetTestFilesDir() const
{
  return this->testFilesDir;
}

std::shared_ptr<std::vector<unsigned char>> TestSupport::GetDataFromTestFilesDir(const std::string & fileName)
{
  std::string filePath(this->testFilesDir.begin(), this->testFilesDir.end());
  filePath += "/";
  filePath += fileName;

  std::ifstream file(filePath.c_str(), std::ios::binary);
  if (file.bad() || !file.is_open()) {
    throw std::exception(std::string("Cannot open " + filePath).c_str());
  }

  std::shared_ptr<std::vector<unsigned char>> data(new std::vector<unsigned char>());

  size_t fileSize = 0;
  file.seekg(0, std::ios::end);
  fileSize = static_cast<size_t>(file.tellg());
  file.seekg(0, std::ios::beg);

  data->reserve(fileSize);
  data->assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
  return data;
}

TestSupport * TestSupport::instance = nullptr;

void TestSupport::setup(const std::string & appPath)
{
  std::string pathName(appPath.substr(0, appPath.find_last_of('.')));
  fs::path dir(pathName);

  if (!fs::exists(dir)) {
    fs::create_directory(dir);
  }
  std::wstring temp = dir;
  this->testDir.assign(temp.begin(), temp.end());
  this->testFilesDir = "C:/dev/Analyzer/AnalyzerTest/testFiles";
}
