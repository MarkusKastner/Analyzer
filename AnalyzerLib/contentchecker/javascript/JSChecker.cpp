/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "AnalyzerLib/contentchecker/javascript/JSChecker.h"

namespace analyzer {
  namespace checker {
    JSChecker::JSChecker()
      :data(), iCaseChecker()
    {
    }

    JSChecker::~JSChecker()
    {
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
        this->iCaseChecker.reset(new JSICaseChecker(this->data));
      }
      return this->iCaseChecker->IsMyCase(offset);
    }
  }
}