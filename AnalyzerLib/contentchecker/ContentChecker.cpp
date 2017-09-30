#include "ContentChecker.h"

#include "CheckObserver.h"

namespace analyzer {
  namespace checker {
    ContentChecker::~ContentChecker()
    {
    }

    size_t ContentChecker::GetNumCheckObservers() const
    {
      return this->checkObservers.size();
    }

    void ContentChecker::RegisterCheckObserver(CheckObserver * observer)
    {
      for (auto& existing : this->checkObservers) {
        if (existing == observer) {
          return;
        }
      }
      this->checkObservers.push_back(observer);
    }

    void ContentChecker::UnregisterCheckObserver(CheckObserver * observer)
    {
      std::vector<CheckObserver*>::iterator end = this->checkObservers.end();

      for (auto it = this->checkObservers.begin(); it != end; ++it) {
        if ((*it) == observer) {
          it = this->checkObservers.erase(it);
          return;
        }
      }
    }

    ContentChecker::ContentChecker()
      :checkObservers()
    {
    }
  }
}