/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "AnalyzerLib/contentchecker/javascript/JSVCaseChecker.h"
#include "AnalyzerLib/contentchecker/SyntaxCheckerParent.h"
#include "AnalyzerLib/contentchecker/ContentChecker.h"

namespace analyzer {
  namespace checker {
    JSVCaseChecker::JSVCaseChecker(SyntaxCheckerParent * parent)
      :parent(parent), data()
    {
      if (parent == nullptr) {
        throw - 1;
      }
      this->data = this->parent->GetData();
    }

    JSVCaseChecker::~JSVCaseChecker()
    {
    }

    bool JSVCaseChecker::HasData() const
    {
      if (!data) {
        return false;
      }
      return !this->data->empty();
    }

    void JSVCaseChecker::SetData(const std::shared_ptr<std::vector<unsigned char>>& data)
    {
      this->data = data;
    }

    void JSVCaseChecker::ReleaseData()
    {
      this->data.reset();
    }

    bool JSVCaseChecker::IsMyCase(const size_t & offset)
    {
      if (ContentChecker::RangeToString(offset, JSVCaseChecker::KeyWord_var.size(), this->data).compare(JSVCaseChecker::KeyWord_var) == 0) {
        return this->isVarCase(offset);
      }
      return false;
    }

    bool JSVCaseChecker::isVarCase(const size_t & offset)
    {
      unsigned char preByte = ' ';
      unsigned char postByte = ' ';

      if (ContentChecker::HasPreByte(offset)) {
        preByte = this->data->at(offset - 1);
      }

      if (!ContentChecker::IsByteSpace(preByte)) {
        if (ContentChecker::IsByteABC(preByte) || ContentChecker::IsByteNum(preByte)) {
          return false;
        }
        if (preByte != '(' && preByte != ';') {
          return false;
        }
      }

      if (ContentChecker::HasPostByte(offset, JSVCaseChecker::KeyWord_var.size(), this->data)) {
        postByte = this->data->at(offset + JSVCaseChecker::KeyWord_var.size());
      }

      if (!ContentChecker::IsByteSpace(postByte)) {
        return false;
      }

      postByte = ContentChecker::FindNextNoneSpacePrintable(offset + JSVCaseChecker::KeyWord_var.size(), this->data);
      if (!ContentChecker::IsByteABC(postByte)) {
        return false;
      }
      this->parent->SetLastFoundSyntaxOffset(JSVCaseChecker::KeyWord_var.size());
      return true;
    }

    const std::string JSVCaseChecker::KeyWord_var = "var";
  }
}