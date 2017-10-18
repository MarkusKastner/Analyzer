/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "AnalyzerLib/contentchecker/javascript/JSFCaseChecker.h"
#include "AnalyzerLib/contentchecker/SyntaxCheckerParent.h"
#include "AnalyzerLib/contentchecker/ContentChecker.h"

namespace analyzer {
  namespace checker {
    JSFCaseChecker::JSFCaseChecker(SyntaxCheckerParent * parent)
      :parent(parent), data()
    {
      if (parent == nullptr) {
        throw - 1;
      }
      this->data = this->parent->GetData();
    }

    JSFCaseChecker::~JSFCaseChecker()
    {
    }

    bool JSFCaseChecker::HasData() const
    {
      if (!data) {
        return false;
      }
      return !this->data->empty();
    }

    void JSFCaseChecker::SetData(const std::shared_ptr<std::vector<unsigned char>>& data)
    {
      this->data = data;
    }

    void JSFCaseChecker::ReleaseData()
    {
      this->data.reset();
    }

    bool JSFCaseChecker::IsMyCase(const size_t & offset)
    {
      if (ContentChecker::RangeToString(offset, JSFCaseChecker::KeyWord_for.size(), this->data).compare(JSFCaseChecker::KeyWord_for) == 0) {
        return this->isForCase(offset);
      }
      return false;
    }


    bool JSFCaseChecker::isForCase(const size_t & offset)
    {
      if (ContentChecker::IsByteBeforeSpace(offset, this->data)) {
        if (ContentChecker::FindNextNoneSpacePrintable(offset + JSFCaseChecker::KeyWord_for.size(), this->data) == '(') {
          this->parent->SetLastFoundSyntaxOffset(JSFCaseChecker::KeyWord_for.size());
          return true;
        }
      }
      return false;
    }

    const std::string JSFCaseChecker::KeyWord_for = "for";
  }
}