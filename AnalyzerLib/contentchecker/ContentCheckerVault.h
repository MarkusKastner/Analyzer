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

      size_t GetNumCheckers() const;

      void InitializeExtraordinaryChecker();
      void InitializeExecutableChecker();
      void InitializeExternalLinkChecker();
      void InitializeMacroChecker();

      bool HasExtraordinaryChecker() const;
      bool HasExecutableChecker() const;
      bool HasExternalLinkChecker() const;
      bool HasMacroChecker() const;

      void RegisterCheckObserver(CheckObserver * observer);
      void UnregisterCheckObserver(CheckObserver * observer);

      void RunChecker();
      void SetCurrentData(const std::shared_ptr<std::vector<unsigned char>> & data);

    private:
      std::vector<std::shared_ptr<ContentChecker>> contentCheckers;
      std::shared_ptr<std::vector<unsigned char>> data;
      std::vector<CheckObserver*> checkObservers;

      void registerObservers(ContentChecker * contentChecker);
      void unregisterObservers(ContentChecker * contentChecker);
    };
  }
}
#endif