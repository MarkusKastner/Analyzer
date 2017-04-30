/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef PEINTERPRETERTEST_H
#define PEINTERPRETERTEST_H

#include <gtest\gtest.h>

#include "AnalyzerLib\interpreter\PE\PEInterpreter.h"

class PEInterpreterTest : public testing::Test
{
public:
  PEInterpreterTest()
    : testing::Test()
  {
  }

  virtual ~PEInterpreterTest() {}
};

TEST_F(PEInterpreterTest, init)
{
  analyzer::interpreter::PEInterpreter peInterpreter;
  ASSERT_EQ(peInterpreter.GetFileFormat(), analyzer::core::FileFormat::winExec);
}
#endif