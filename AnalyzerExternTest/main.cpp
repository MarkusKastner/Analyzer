/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include <gtest/gtest.h>

#include <string>
#include <filesystem>

#include "network\CrossSockTest.h"

int main(int argc, char** argv) {

  testing::InitGoogleTest(&argc, argv);
  int ret = RUN_ALL_TESTS();

  getchar();

  return ret;
}