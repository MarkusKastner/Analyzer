/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "ContentCheckerVault.h"

#include "AnalyzerLib/contentchecker/ExtraordinaryChecker.h"

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
  }
}