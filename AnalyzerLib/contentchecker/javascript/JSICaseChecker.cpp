/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "AnalyzerLib/contentchecker/javascript/JSICaseChecker.h"
#include "JSICaseChecker.h"
#include "AnalyzerLib/contentchecker/SyntaxCheckerParent.h"

namespace analyzer {
  namespace checker {
    JSICaseChecker::JSICaseChecker(SyntaxCheckerParent * parent)
      :parent(parent), data()
    {
      if (parent == nullptr) {
        throw - 1;
      }
      this->data = this->parent->GetData();
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
      std::string strg;
      size_t length = JSICaseChecker::KeyWord_if.size();
      size_t endOffset = length + offset;

      if (endOffset > this->data->size()) {
        return false;
      }

      for (size_t i = offset; i < endOffset; ++i) {
        strg.push_back(static_cast<char>(this->data->at(i)));
      }

      if (strg.compare(JSICaseChecker::KeyWord_if) == 0) {
        this->parent->SetLastFoundSyntaxOffset(JSICaseChecker::KeyWord_if.size());
        return true;
      }
      return false;
    }

    const std::string JSICaseChecker::KeyWord_if = "if";
  }
}