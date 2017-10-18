/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef JSCHECKER_H
#define JSCHECKER_H

#include <memory>
#include <vector>

#include "AnalyzerLib/contentchecker/javascript/JSICaseChecker.h"
#include "AnalyzerLib/contentchecker/javascript/JSFCaseChecker.h"
#include "AnalyzerLib/contentchecker/SyntaxCheckerParent.h"

namespace analyzer {
  namespace checker {
    class JSChecker : public SyntaxCheckerParent
    {
    public:
      JSChecker();
      ~JSChecker();

      virtual void SetLastFoundSyntaxOffset(const size_t & offset);
      virtual const std::shared_ptr<std::vector<unsigned char>> & GetData() const;

      bool HasData() const;
      void SetData(const std::shared_ptr<std::vector<unsigned char>> & data);
      void ReleaseData();

      bool IsICaseSyntax(const size_t & offset);
      bool IsFCaseSyntax(const size_t & offset);
      const size_t & GetLastFoundSyntaxOffset() const;

    private:
      std::shared_ptr<std::vector<unsigned char>> data;
      std::unique_ptr<JSICaseChecker> iCaseChecker;
      std::unique_ptr<JSFCaseChecker> fCaseChecker;
      size_t lastFoundSyntaxOffset;
    };
  }
}
#endif