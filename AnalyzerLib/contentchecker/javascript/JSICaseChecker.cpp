/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "AnalyzerLib/contentchecker/javascript/JSICaseChecker.h"
#include "JSICaseChecker.h"

namespace analyzer {
  namespace checker {
    JSICaseChecker::JSICaseChecker(const std::shared_ptr<std::vector<unsigned char>>& data)
      :data(data)
    {
    }

    JSICaseChecker::~JSICaseChecker()
    {
    }

    bool JSICaseChecker::HasData() const
    {
      if (!data) {
        return false;
      }
      return !this->data->empty();
    }

    void JSICaseChecker::SetData(const std::shared_ptr<std::vector<unsigned char>>& data)
    {
      this->data = data;
    }

    void JSICaseChecker::ReleaseData()
    {
      this->data.reset();
    }
    bool JSICaseChecker::IsMyCase(const size_t & offset)
    {
      if (offset == 21) {
        return true;
      }
      return false;
    }
  }
}