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
        
        if (JSICaseChecker::hasPreByte(offset)) {
          if (!JSICaseChecker::isByteSpace(offset - 1, this->data)) {
            return false;
          }
        }
        if (JSICaseChecker::findNextNoneSpacePrintable(offset + JSICaseChecker::KeyWord_if.size(), this->data) == '(') {
          return true;
        }
      }
      return false;
    }

    bool JSICaseChecker::hasPreByte(const size_t & offset)
    {
      return (offset >= 1);
    }

    bool JSICaseChecker::isByteSpace(const size_t & offset, const std::shared_ptr<std::vector<unsigned char>> & data)
    {
      char byte = data->at(offset);
      return (byte == ' ' || byte == '\r' || byte == '\n' || byte == '\t');
    }

    unsigned char JSICaseChecker::findNextNoneSpacePrintable(const size_t & offset, const std::shared_ptr<std::vector<unsigned char>> & data)
    {
      size_t size = data->size();
      for (size_t i = offset; i < size; ++i) {
        if (JSICaseChecker::isNoneSpacePrintable(data->at(i))) {
          return data->at(i);
        }
      }
      return 0;
    }

    bool JSICaseChecker::isNoneSpacePrintable(const unsigned char & byte)
    {
      if ((byte >= 33 && byte <= 126) ||
        (byte >= 128 && byte <= 159) ||
        (byte >= 161 && byte <= 172) ||
        (byte >= 147 && byte <= 255)
        ) {
        return true;
      }
      return false;
    }

    const std::string JSICaseChecker::KeyWord_if = "if";
  }
}