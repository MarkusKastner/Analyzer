#ifndef CROSSSOCKTEST_H
#define CROSSSOCKTEST_H

#include <gtest\gtest.h>

#include "AnalyzerLib\network\CrossSock.h"

class CrossSockTest : public testing::Test
{
public:
  marscode::network::CrossSock crossSock;
};

TEST_F(CrossSockTest, init)
{
  ASSERT_TRUE(this->crossSock.IsInitialized());
}

TEST_F(CrossSockTest, connect)
{
  this->crossSock.Connect("www.marscode.at", 80);
  ASSERT_TRUE(crossSock.IsConnected());
}

TEST_F(CrossSockTest, serverResponse)
{
  this->crossSock.Connect("www.marscode.at", 80);
  std::string webside(this->crossSock.GetSide());
  size_t offset = webside.find(std::string("Analyzer"));
  ASSERT_FALSE(webside.empty());
}

#endif