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
#include "definitions/DefinitionDBTest.h"
#include "definitions/DefinitionVaultTest.h"
#include "definitions/DefinitionSourceTest.h"
#include "definitions/LocalDefinitionTest.h"
#include "definitions/DefinitionTest.h"
#include "definitions/TextDefinitionTest.h"
#include "strategy/AnalyzingStrategyTest.h"
#include "strategy/ResultTest.h"
#include "strategy/xml/XMLStrategyTest.h"
#include "interpreter/formatter/FormatterTest.h"
#include "interpreter/formatter/XMLFormatterTest.h"
#include "interpreter/formatter/SimpleTextFormatterTest.h"
#include "interpreter/formatter/BitFormatterTest.h"
#include "interpreter/formatter/HexFormatterTest.h"
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

int main(int argc, char** argv) {

  std::string path(argv[0]);
  TestSupport::Initialize(path);

  testing::InitGoogleTest(&argc, argv);
  int ret = RUN_ALL_TESTS();

  getchar();

  return ret;
}