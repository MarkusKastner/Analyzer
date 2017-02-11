/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef ANALYZERBASEOBSERVER_H
#define ANALYZERBASEOBSERVER_H

#include "AnalyzerLib\base\AnalyzingOptions.h"

namespace analyzer{
  namespace base{
    class AnalyzerBaseObserver
    {
    public:
      virtual void NotifyInterprterChange() = 0;
      virtual void NotifyDocumentChange() = 0;
      virtual void AddBinaryLine(const std::string & hex, const std::string & binary, const std::string & ascii, const std::string & numerical) = 0;
      virtual void ClearBinaryView() = 0;
      virtual void AddOutputMessage(const std::string & message) = 0;
      virtual void SetAvailableAnalyzingOptions(const base::AnalyzingOptions & analyzingOptions) = 0;
    };
  }
}
#endif