#ifndef UPDATETEST_H
#define UPDATETEST_H

#include <gtest\gtest.h>
#include "AnalyzerLib\service\Update.h"

class UpdateTest : public testing::Test
{

};

TEST_F(UpdateTest, init)
{
  analyzer::service::Update update;
  ASSERT_TRUE(update.Connect("www.marscodea.at", 80));
}

#endif