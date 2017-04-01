/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef TESTSUPPORT_H
#define TESTSUPPORT_H

#include <string>
#include <exception>
#include <memory>
#include <vector>

class TestSupport
{
public:
  ~TestSupport();

  static void Initialize(const std::string & appPath);
  static TestSupport * GetInstance();

  const std::string & GetTestDir() const;
  const std::string & GetTestFilesDir() const;
  std::shared_ptr<std::vector<unsigned char>> GetDataFromTestFilesDir(const std::string & fileName);

private:
  TestSupport();
  std::string testDir;
  std::string testFilesDir;
  static TestSupport * instance;

  void setup(const std::string & appPath);
};

#endif