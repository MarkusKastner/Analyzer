/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef CONTENTCHECKER_H
#define CONTENTCHECKER_H

#include <vector>
#include <memory>

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

      bool HasData();
      void SetData(const std::shared_ptr<std::vector<unsigned char>> & data);

    protected:
      ContentChecker();

    private:
      std::vector<CheckObserver*> checkObservers;
      base::AnalyzerRGB workingColor;
      std::shared_ptr<std::vector<unsigned char>> data;
    };
  }
}
#endif