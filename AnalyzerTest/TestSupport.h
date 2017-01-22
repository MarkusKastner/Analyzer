/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef TESTSUPPORT_H
#define TESTSUPPORT_H

#include <string>
#include <exception>

class TestSupport
{
public:
  ~TestSupport();

  static void Initialize(const std::string & appPath);
  static TestSupport * GetInstance();

  const std::wstring & GetTestDir() const;
  const std::wstring & GetTestFilesDir() const;

private:
  TestSupport();
  std::wstring testDir;
  std::wstring testFilesDir;
  static TestSupport * instance;

  void setup(const std::string & appPath);
};

#endif