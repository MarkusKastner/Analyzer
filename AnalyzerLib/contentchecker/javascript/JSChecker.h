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

namespace analyzer {
  namespace checker {
    class JSChecker
    {
    public:
      JSChecker();
      ~JSChecker();

      bool HasData() const;
      void SetData(const std::shared_ptr<std::vector<unsigned char>> & data);
      void ReleaseData();

      bool IsICaseSyntax(const size_t & offset);

    private:
      std::shared_ptr<std::vector<unsigned char>> data;
      std::unique_ptr<JSICaseChecker> iCaseChecker;
    };
  }
}
#endif