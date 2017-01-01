#ifndef DEFINITIONVAULTTEST_H
#define DEFINITIONVAULTTEST_H

#include <gtest\gtest.h>
#include <memory>

#include "AnalyzerLib\base\DefinitionVault.h"
#include "AnalyzerLib\base\error\DBException.h"
#include "AnalyzerLib\base\DefinitionSource.h"
#include "AnalyzerLib\base\LocalDefinition.h"

class DefinitionVaultTest : public testing::Test
{
public:

  void SetUp(){
    asciiSource.AddSource(std::shared_ptr<analyzer::base::DefinitionSource>(new analyzer::base::LocalDefinition("default_ascii")));
  }

  analyzer::base::DefinitionVault emptySource;
  analyzer::base::DefinitionVault asciiSource;
};

TEST_F(DefinitionVaultTest, init)
{
  ASSERT_FALSE(emptySource.HasDefinitions());
}

TEST_F(DefinitionVaultTest, AddSource)
{
  emptySource.AddSource(std::shared_ptr<analyzer::base::DefinitionSource>(new analyzer::base::LocalDefinition("default_ascii")));
  ASSERT_STREQ(emptySource.GetSourceAt(0)->GetName().c_str(), "default_ascii");
}

TEST_F(DefinitionVaultTest, NumSources)
{
  ASSERT_EQ(asciiSource.GetNumSources(), 1);
}

TEST_F(DefinitionVaultTest, GetSourceAt)
{
  ASSERT_STREQ(asciiSource.GetSourceAt(0)->GetName().c_str(), "default_ascii");
}

#endif