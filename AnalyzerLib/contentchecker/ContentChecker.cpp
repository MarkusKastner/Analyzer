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

    ContentChecker::ContentChecker()
      :checkObservers()
    {
    }
  }
}