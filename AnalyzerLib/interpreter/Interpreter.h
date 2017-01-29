/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <memory>
#include <string>
#include <vector>

#include "AnalyzerLib\base\BaseData.h"

namespace analyzer{
  namespace interpreter{
    class TextChangedObserver;
    class TextGlyph;
    class Interpreter
    {
    public:
      virtual bool HasData() = 0;
      virtual void ResetData(const std::shared_ptr<std::vector<unsigned char>> & data) = 0;
      virtual std::shared_ptr<std::vector<unsigned char>> GetData() = 0;

      virtual std::shared_ptr<std::wstring> GetText() = 0;
      virtual std::vector<std::wstring> GetFunctionalHighlightExpressions() = 0;

      virtual bool HasObservers() = 0;
      virtual size_t NumberOfObservers() = 0;
      virtual void RegisterObserver(TextChangedObserver * observer) = 0;
      virtual void UnregisterObserver(TextChangedObserver * observer) = 0;
      virtual void NotifyTextChange() = 0;

      virtual void SetDetailFormat(const base::DetailFormat & detailFormat, bool forceNotify = false) = 0;
    };
  }
}
#endif