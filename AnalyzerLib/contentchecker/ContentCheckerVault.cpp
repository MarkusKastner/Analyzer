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
      :contentCheckers()
    {
    }

    ContentCheckerVault::~ContentCheckerVault()
    {
    }

    size_t ContentCheckerVault::GetNumCheckers() const
    {
      return this->contentCheckers.size();
    }

    void ContentCheckerVault::InitializeExtraordinaryChecker()
    {
      this->contentCheckers.push_back(std::unique_ptr<ContentChecker>(new ExtraordinaryChecker()));
    }

    void ContentCheckerVault::InitializeExecutableChecker()
    {
      this->contentCheckers.push_back(std::unique_ptr<ContentChecker>(new ExecutableChecker()));
    }

    void ContentCheckerVault::InitializeExternalLinkChecker()
    {
      this->contentCheckers.push_back(std::unique_ptr<ContentChecker>(new ExternalLinkChecker()));
    }

    void ContentCheckerVault::InitializeMacroChecker()
    {
      this->contentCheckers.push_back(std::unique_ptr<ContentChecker>(new MacroChecker()));
    }

    bool ContentCheckerVault::HasExtraordinaryChecker() const
    {
      for (auto& contentChecker : this->contentCheckers) {
        if (dynamic_cast<ExtraordinaryChecker*>(contentChecker.get())) {
          return true;
        }
      }
      return false;
    }

    bool ContentCheckerVault::HasExecutableChecker() const
    {
      for (auto& contentChecker : this->contentCheckers) {
        if (dynamic_cast<ExecutableChecker*>(contentChecker.get())) {
          return true;
        }
      }
      return false;
    }

    bool ContentCheckerVault::HasExternalLinkChecker() const
    {
      for (auto& contentChecker : this->contentCheckers) {
        if (dynamic_cast<ExternalLinkChecker*>(contentChecker.get())) {
          return true;
        }
      }
      return false;
    }

    bool ContentCheckerVault::HasMacroChecker() const
    {
      for (auto& contentChecker : this->contentCheckers) {
        if (dynamic_cast<MacroChecker*>(contentChecker.get())) {
          return true;
        }
      }
      return false;
    }
  }
}