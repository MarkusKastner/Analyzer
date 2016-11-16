#include <gtest/gtest.h>

#include "core\ByteTest.h"

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);

  int ret = RUN_ALL_TESTS();

  getchar();

  return ret;
}