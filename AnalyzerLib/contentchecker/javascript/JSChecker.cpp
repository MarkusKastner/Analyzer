/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "AnalyzerLib/contentchecker/javascript/JSChecker.h"

namespace analyzer {
  namespace checker {
    JSChecker::JSChecker()
      :data(), iCaseChecker(), lastFoundSyntaxOffset(0)
    {
    }

    JSChecker::~JSChecker()
    {
    }

    void JSChecker::SetLastFoundSyntaxOffset(const size_t & offset)
    {
      this->lastFoundSyntaxOffset = offset;
    }

    const std::shared_ptr<std::vector<unsigned char>> & JSChecker::GetData() const
    {
      return this->data;
    }

    bool JSChecker::HasData() const
    {
      if (!data) {
        return false;
      }
      return !this->data->empty();
    }

    void JSChecker::SetData(const std::shared_ptr<std::vector<unsigned char>>& data)
    {
      this->data = data;
    }

    void JSChecker::ReleaseData()
    {
      if (this->iCaseChecker) {
        this->iCaseChecker->ReleaseData();
      }
      data.reset();
    }

    bool JSChecker::IsICaseSyntax(const size_t & offset)
    {
      if (!this->iCaseChecker) {
        this->iCaseChecker.reset(new JSICaseChecker(this));
      }
      if (this->iCaseChecker->IsMyCase(offset)) {
        return true;
      }
      return false;
    }
    const size_t & JSChecker::GetLastFoundSyntaxOffset() const
    {
      return this->lastFoundSyntaxOffset;
    }
  }
}