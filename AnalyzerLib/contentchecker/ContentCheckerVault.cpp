/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "ContentCheckerVault.h"

#include "AnalyzerLib/contentchecker/ExtraordinaryChecker.h"
#include "AnalyzerLib/contentchecker/ExecutableChecker.h"
#include "AnalyzerLib/contentchecker/ExternalLinkChecker.h"
#include "AnalyzerLib/contentchecker/MacroChecker.h"

namespace analyzer {
  namespace checker {
    ContentCheckerVault::ContentCheckerVault()
    {
    }

    ContentCheckerVault::~ContentCheckerVault()
    {
    }

    size_t ContentCheckerVault::GetNumCheckers()
    {
      return size_t(0);
    }

    ContentChecker * ContentCheckerVault::CreateExtraordinaryChecker()
    {
      return new ExtraordinaryChecker();
    }

    ContentChecker * ContentCheckerVault::CreateExecutableChecker()
    {
      return new ExecutableChecker();
    }

    ContentChecker * ContentCheckerVault::CreateExternalLinkChecker()
    {
      return new ExternalLinkChecker();
    }

    ContentChecker * ContentCheckerVault::CreateMacroChecker()
    {
      return new MacroChecker();
    }
  }
}