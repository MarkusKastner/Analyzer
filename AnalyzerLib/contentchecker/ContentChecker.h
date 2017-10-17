/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef CONTENTCHECKER_H
#define CONTENTCHECKER_H

#include <vector>
#include <memory>
#include <atomic>
#include <thread>

#include "AnalyzerLib/base/BaseData.h"

namespace analyzer {
  namespace checker {
    class CheckObserver;
    class ContentChecker
    {
    public:
      virtual ~ContentChecker();

      size_t GetNumCheckObservers() const;
      void RegisterCheckObserver(CheckObserver * observer);
      void UnregisterCheckObserver(CheckObserver * observer);

      void SetWorkingColor(const base::AnalyzerRGB & color);
      const base::AnalyzerRGB & GetWorkingColor() const;
      void ClearWorkerMarkings();
      void MarkSuspectRange(const size_t & index, const size_t & offset);

      bool HasData();
      virtual void SetData(const std::shared_ptr<std::vector<unsigned char>> & data);
      virtual void ReleaseData();

      void SetCheckRange(const size_t & startOffset, const size_t & checkOffset);
      const size_t & GetStartOffest() const;
      const size_t & GetCheckOffest() const;

      bool IsChecking() const;
      void StartCheck();
      void StopCheck();
      bool IsFinished() const;

      std::string RangeToString(const size_t & offset, const size_t & length) const;
      static std::string RangeToString(const size_t & offset, const size_t & length, const std::shared_ptr<std::vector<unsigned char>> & data);

      const size_t & GetSearchPos() const;
      const size_t & StepUpSearchPos();
      void SetSearchPos(const size_t & searchPos);
      bool SearchDone();

    protected:
      ContentChecker();

      virtual void checkData() = 0;
      
      const std::shared_ptr<std::vector<unsigned char>> & getData();
      void notifyCurrentIndex(const size_t index);
      void notifyMarkedIndex(const size_t index);
      void notifyClearWorkingMarkings();
      void notifySuspectRange(const size_t & index, const size_t & offset);

    private:
      std::vector<CheckObserver*> checkObservers;
      base::AnalyzerRGB workingColor;
      std::shared_ptr<std::vector<unsigned char>> data;
      size_t startOffest;
      size_t checkOffest;
      std::atomic<bool> runCheck;
      std::atomic<bool> finished;
      std::unique_ptr<std::thread> checkThread;
      size_t searchPos;
      bool searchDone;

      void checkRoutine();
      void notifyCheckFinished();
    };
  }
}
#endif