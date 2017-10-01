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

    void ContentChecker::SetWorkingColor(const base::AnalyzerRGB & color)
    {
      this->workingColor = color;
    }

    const base::AnalyzerRGB & ContentChecker::GetWorkingColor() const
    {
      return this->workingColor;
    }

    bool ContentChecker::HasData()
    {
      return (this->data.get() != nullptr);
    }

    void ContentChecker::SetData(const std::shared_ptr<std::vector<unsigned char>>& data)
    {
      this->data = data;
      this->checkOffest = this->data->size();
    }

    void ContentChecker::ReleaseData()
    {
      if (this->data) {
        this->data.reset();
      }
    }

    void ContentChecker::SetCheckRange(const size_t & startOffset, const size_t & checkOffset)
    {
      this->startOffest = startOffset;
      this->checkOffest = checkOffset;
    }

    const size_t & ContentChecker::GetStartOffest() const
    {
      return this->startOffest;
    }

    const size_t & ContentChecker::GetCheckOffest() const
    {
      return this->checkOffest;
    }

    bool ContentChecker::IsChecking() const
    {
      return this->runCheck.load();
    }

    void ContentChecker::StartCheck()
    {
      this->runCheck = true;
    }

    ContentChecker::ContentChecker()
      :checkObservers(), workingColor({0,0,0}), data(),
      startOffest(0), checkOffest(0), runCheck(false)
    {
    }
  }
}