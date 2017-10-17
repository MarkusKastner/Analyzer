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

    bool JSICaseChecker::hasPreByte(const size_t & offset)
    {
      return (offset >= 1);
    }

    bool JSICaseChecker::isByteSpace(const size_t & offset, const std::shared_ptr<std::vector<unsigned char>> & data)
    {
      return JSICaseChecker::isByteSpace(data->at(offset));
    }

    bool JSICaseChecker::isByteSpace(const unsigned char & byte)
    {
      return (byte == ' ' || byte == '\r' || byte == '\n' || byte == '\t');
    }

    bool JSICaseChecker::isByteBeforeSpace(const size_t & offset, const std::shared_ptr<std::vector<unsigned char>>& data)
    {
      if (JSICaseChecker::hasPreByte(offset)) {
        return JSICaseChecker::isByteSpace(offset - 1, data);
      }
      return false;
    }

    bool JSICaseChecker::isByteBeforeLineFeed(const size_t & offset, const std::shared_ptr<std::vector<unsigned char>>& data)
    {
      if (!JSICaseChecker::hasPreByte(offset)) {
        return false;
      }
      if (!(data->at(offset - 1) == '\n' && JSICaseChecker::hasPreByte(offset - 1))) {
        return false;
      }
      if (data->at(offset - 2) == '\r'){
        return true;
      }
      return false;
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

    std::string JSICaseChecker::findWordBeforeOffset(const size_t numWordsBefore, const size_t & offset, const std::shared_ptr<std::vector<unsigned char>>& data)
    {
      std::string foundWord;
      bool assemblingWordActive = false;
      size_t wordCounter = 0;
      for (size_t i = offset - 1; i != 0; --i) {
        if (!JSICaseChecker::isByteSpace(i, data)) {
          if (!assemblingWordActive) {
            wordCounter++;
          }
          assemblingWordActive = true;
        }
        else {
          if (assemblingWordActive && wordCounter >= numWordsBefore) {
            break;
          }
          assemblingWordActive = false;
          foundWord = "";
        }
        if (assemblingWordActive) {
          foundWord.insert(foundWord.begin(), data->at(i));
        }
      }
      return foundWord;
    }

    bool JSICaseChecker::lastByteInLineIs(const unsigned char value, const size_t & offset, const std::shared_ptr<std::vector<unsigned char>>& data)
    {
      auto lineBytes(JSICaseChecker::getRestOfLineWithoutLF(offset, data, true));
      if (!lineBytes.empty()) {
        return lineBytes.back() == value;
      }
      return false;
    }

    std::vector<unsigned char> JSICaseChecker::getRestOfLineWithoutLF(const size_t & offset, const std::shared_ptr<std::vector<unsigned char>>& data, const bool & skipSpaces)
    {
      std::vector<unsigned char> lineBytes;
      auto size = data->size();
      for (size_t i = offset; i < size; ++i) {
        char currentByte = data->at(i);
        if (currentByte != '\r') {
          if (skipSpaces && JSICaseChecker::isByteSpace(currentByte)) {
            continue;
          }
          else {
            lineBytes.push_back(currentByte);
          }
        }
        else {
          break;
        }
      }
      return lineBytes;
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

    bool JSICaseChecker::isIfCase(const size_t & offset)
    {
      if (JSICaseChecker::isByteBeforeSpace(offset, this->data)) {
        if (JSICaseChecker::findNextNoneSpacePrintable(offset + JSICaseChecker::KeyWord_if.size(), this->data) == '(') {
          this->parent->SetLastFoundSyntaxOffset(JSICaseChecker::KeyWord_if.size());
          return true;
        }
      }
      return false;
    }

    bool JSICaseChecker::isImplementsCase(const size_t & offset)
    {
      if (JSICaseChecker::isByteBeforeSpace(offset, this->data)) {

        std::string foundWord = JSICaseChecker::findWordBeforeOffset(2, offset, this->data);

        if (!foundWord.empty() && foundWord.compare("class") == 0) {
          this->parent->SetLastFoundSyntaxOffset(JSICaseChecker::KeyWord_implements.size());
          return true;
        }
      }
      return false;
    }

    bool JSICaseChecker::isImportCase(const size_t & offset)
    {
      if (JSICaseChecker::isByteBeforeLineFeed(offset, this->data) && JSICaseChecker::lastByteInLineIs(';', offset + JSICaseChecker::KeyWord_import.size(), this->data)) {
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