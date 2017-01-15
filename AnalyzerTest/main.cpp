/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include <gtest/gtest.h>

#include <string>
#include <filesystem>

#include "core\ByteTest.h"
#include "core\BasicTypeTest.h"
#include "core\WordTest.h"
#include "core\ByteCollectionTest.h"
#include "interpreter\BinaryStyleInterpreterTest.h"
#include "interpreter\TextStyleInterpreterTest.h"
#include "interpreter\TextChangedObserverTest.h"
#include "base\AnalyzerBaseTest.h"
#include "core\zip\ZIPContainerTest.h"
#include "core\FileTest.h"
#include "definitions\DefinitionDBTest.h"
#include "definitions\DefinitionVaultTest.h"
#include "definitions\DefinitionSourceTest.h"
#include "definitions\LocalDefinitionTest.h"
#include "definitions\DefinitionTest.h"
#include "definitions\TextDefinitionTest.h"
#include "strategy\AnalyzingStrategyTest.h"
#include "strategy\ResultTest.h"
#include "strategy\xml\XMLStrategyTest.h"
#include "core\FormatFinderTest.h"
#include "interpreter\formatter\FormatterTest.h"
#include "interpreter\formatter\XMLFormatterTest.h"
#include "interpreter\formatter\SimpleTextFormatterTest.h"
#include "interpreter\formatter\BitFormatterTest.h"

namespace fs = std::tr2::sys;
fs::path testDir;

void setupTestDir(const std::string appPath)
{
  fs::path app(appPath);
  fs::path dir(std::string(app.remove_filename().string() + "/" + app.basename().c_str()));

  if (!fs::exists(dir)){
    fs::create_directory(dir);
  }
  testDir = dir;
}

int main(int argc, char** argv) {

  std::string path(argv[0]);
  setupTestDir(path);

  testing::InitGoogleTest(&argc, argv);
  int ret = RUN_ALL_TESTS();

  getchar();

  return ret;
}