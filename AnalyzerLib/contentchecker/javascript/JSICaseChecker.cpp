/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "AnalyzerLib/contentchecker/javascript/JSICaseChecker.h"
#include "JSICaseChecker.h"
#include "AnalyzerLib/contentchecker/SyntaxCheckerParent.h"
#include "AnalyzerLib/contentchecker/ContentChecker.h"

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
      if (ContentChecker::RangeToString(offset, JSICaseChecker::KeyWord_if.size(), this->data).compare(JSICaseChecker::KeyWord_if) == 0) {
        return this->isIfCase(offset);
      }
      if (ContentChecker::RangeToString(offset, JSICaseChecker::KeyWord_implements.size(), this->data).compare(JSICaseChecker::KeyWord_implements) == 0) {
        return this->isImplementsCase(offset);
      }
      if (ContentChecker::RangeToString(offset, JSICaseChecker::KeyWord_import.size(), this->data).compare(JSICaseChecker::KeyWord_import) == 0) {
        return this->isImportCase(offset);
      }
      return false;
    }


    bool JSICaseChecker::isIfCase(const size_t & offset)
    {
      if (ContentChecker::IsByteBeforeSpace(offset, this->data)) {
        if (ContentChecker::FindNextNoneSpacePrintable(offset + JSICaseChecker::KeyWord_if.size(), this->data) == '(') {
          this->parent->SetLastFoundSyntaxOffset(JSICaseChecker::KeyWord_if.size());
          return true;
        }
      }
      return false;
    }

    bool JSICaseChecker::isImplementsCase(const size_t & offset)
    {
      if (ContentChecker::IsByteBeforeSpace(offset, this->data)) {

        std::string foundWord = ContentChecker::FindWordBeforeOffset(2, offset, this->data);

        if (!foundWord.empty() && foundWord.compare("class") == 0) {
          this->parent->SetLastFoundSyntaxOffset(JSICaseChecker::KeyWord_implements.size());
          return true;
        }
      }
      return false;
    }

    bool JSICaseChecker::isImportCase(const size_t & offset)
    {
      if (ContentChecker::IsByteBeforeLineFeed(offset, this->data) && ContentChecker::LastByteInLineIs(';', offset + JSICaseChecker::KeyWord_import.size(), this->data)) {
        this->parent->SetLastFoundSyntaxOffset(JSICaseChecker::KeyWord_import.size());
        return true;
      }
      return false;
    }

    const std::string JSICaseChecker::KeyWord_if = "if";
    const std::string JSICaseChecker::KeyWord_implements = "implements";
    const std::string JSICaseChecker::KeyWord_import = "import";
  }
}