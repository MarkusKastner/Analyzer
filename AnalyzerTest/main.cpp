/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include <gtest/gtest.h>

#include <string>
#include <filesystem>

#include "TestSupport.h"
#include "base/AnalyzerBaseTest.h"
#include "core/zip/ZIPContainerTest.h"
#include "core/FileTest.h"
#include "service/UpdateTest.h"
#include "interpreter/InterpreterFactoyTest.h"
#include "interpreter/ASCIIInterpreterTest.h"
#include "core/TypeAnalyzerTest.h"
#include "interpreter/XMLInterpreterTest.h"
#include "interpreter/HTML/HTMLDocumentTest.h"
#include "interpreter/BMPInterpreterTest.h"
#include "interpreter/formatter/ASCIIFormatterTest.h"
#include "interpreter/pdf/PDFInterpreterTest.h"
#include "interpreter/HEXInterpreterTest.h"
#include "cast/CastPoolTest.h"
#include "cast/CastFactoryTest.h"
#include "interpreter/PE/PEInterpreterTest.h"
#include "base/ApplicationSettingsTest.h"
#include "contentchecker/ContentCheckerTest.h"
#include "contentchecker/ContentCheckerVaultTest.h"
#include "contentchecker/ExtraordinaryCheckerTest.h"
#include "contentchecker/ExecutableCheckerTest.h"
#include "contentchecker/ExternalLinkCheckerTest.h"
#include "contentchecker/MacroCheckerTest.h"
#include "contentchecker/javascript/JSCheckerTest.h"
#include "contentchecker/javascript/JSICaseCheckerTest.h"

int main(int argc, char** argv) {

  std::string path(argv[0]);
  TestSupport::Initialize(path);

  testing::InitGoogleTest(&argc, argv);
  int ret = RUN_ALL_TESTS();

  getchar();

  return ret;
}