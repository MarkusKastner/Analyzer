#include <gtest/gtest.h>

#include "core\ByteTest.h"
#include "core\BasicTypeTest.h"
#include "core\WordTest.h"
#include "core\ByteCollectionTest.h"

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);

  int ret = RUN_ALL_TESTS();

  getchar();

  return ret;
}