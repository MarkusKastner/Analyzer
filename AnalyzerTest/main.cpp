#include <gtest/gtest.h>

#include "core\ByteTest.h"
#include "core\BasicTypeTest.h"
#include "core\WordTest.h"
#include "core\ByteCollectionTest.h"
#include "interpreter\BinaryStyleInterpreterTest.h"
#include "interpreter\TextStyleInterpreterTest.h"
#include "interpreter\TextGlyphTest.h"
#include "interpreter\strategy\InterpreterStrategyTest.h"
#include "interpreter\strategy\DefaultTextTest.h"
#include "interpreter\TextChangedObserverTest.h"
#include "base\AnalyzerBaseTest.h"
#include "core\zip\ZIPContainerTest.h"
#include "core\FileTest.h"
#include "definitions\DefinitionDBTest.h"
#include "definitions\DefinitionVaultTest.h"
#include "definitions\DefinitionSourceTest.h"
#include "definitions\LocalDefinitionTest.h"
#include "definitions\DefinitionTest.h"

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);

  int ret = RUN_ALL_TESTS();

  getchar();

  return ret;
}