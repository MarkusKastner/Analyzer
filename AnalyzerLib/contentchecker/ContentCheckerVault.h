/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef CONTENTCHECKERVAULT_H
#define CONTENTCHECKERVAULT_H

#include <vector>
#include <memory>
#include <atomic>
#include <thread>

#include "AnalyzerLib/base/BaseData.h"
#include "ContentChecker.h"

namespace analyzer {
  namespace checker {
    class ContentCheckerVault
    {
    public:
      ContentCheckerVault();
      ~ContentCheckerVault();

      size_t GetNumCheckers();

      ContentChecker * CreateExtraordinaryChecker();
    };
  }
}
#endif