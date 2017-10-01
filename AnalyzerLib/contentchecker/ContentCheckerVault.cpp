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
      :contentCheckers(), data(), checkObservers()
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
      if (!this->data) {
        return;
      }
      std::shared_ptr<ContentChecker> checker(new ExtraordinaryChecker());
      checker->SetWorkingColor({ 0, 255, 255 });
      this->registerObservers(checker.get());
      this->contentCheckers.push_back(checker);
    }

    void ContentCheckerVault::InitializeExecutableChecker()
    {
      if (!this->data) {
        return;
      }
      std::shared_ptr<ContentChecker> checker(new ExecutableChecker());
      checker->SetWorkingColor({ 255, 0, 0 });
      this->registerObservers(checker.get());
      this->contentCheckers.push_back(checker);
    }

    void ContentCheckerVault::InitializeExternalLinkChecker()
    {
      if (!this->data) {
        return;
      }
      std::shared_ptr<ContentChecker> checker(new ExternalLinkChecker());
      checker->SetWorkingColor({ 255, 51, 204 });
      this->registerObservers(checker.get());
      this->contentCheckers.push_back(checker);
    }

    void ContentCheckerVault::InitializeMacroChecker()
    {
      if (!this->data) {
        return;
      }
      std::shared_ptr<ContentChecker> checker(new MacroChecker());
      checker->SetWorkingColor({ 0, 255, 0 });
      checker->SetData(this->data);
      this->registerObservers(checker.get());
      this->contentCheckers.push_back(checker);
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

    void ContentCheckerVault::RegisterCheckObserver(CheckObserver * observer)
    {
      for (auto& existing : this->checkObservers) {
        if (existing == observer) {
          return;
        }
      }
      this->checkObservers.push_back(observer);
    }

    void ContentCheckerVault::UnregisterCheckObserver(CheckObserver * observer)
    {
      std::vector<CheckObserver*>::iterator end = this->checkObservers.end();

      for (auto it = this->checkObservers.begin(); it != end; ++it) {
        if ((*it) == observer) {
          it = this->checkObservers.erase(it);
          return;
        }
      }
    }

    void ContentCheckerVault::RunChecker()
    {
      for (auto& contentChecker : this->contentCheckers) {
        contentChecker->StartCheck();
      }
    }

    void ContentCheckerVault::SetCurrentData(const std::shared_ptr<std::vector<unsigned char>> & data)
    {
      this->data = data;
    }

    void ContentCheckerVault::registerObservers(ContentChecker * contentChecker)
    {
      for (auto& observer : this->checkObservers) {
        contentChecker->RegisterCheckObserver(observer);
      }
    }

    void ContentCheckerVault::unregisterObservers(ContentChecker * contentChecker)
    {
      for (auto& observer : this->checkObservers) {
        contentChecker->UnregisterCheckObserver(observer);
      }
    }
  }
}