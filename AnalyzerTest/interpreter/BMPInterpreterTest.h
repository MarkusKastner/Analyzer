/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef BMPINTERPRETERTEST_H
#define BMPINTERPRETERTEST_H


#include <gtest\gtest.h>
#include "AnalyzerLib\interpreter\BMPInterpreter.h"

class BMPInterpreterTest : public testing::Test
{
public:
  BMPInterpreterTest()
  {}
  virtual ~BMPInterpreterTest() {}

  void SetUp() {
  }

  analyzer::interpreter::BMPInterpreter interpreter;
};

#endif