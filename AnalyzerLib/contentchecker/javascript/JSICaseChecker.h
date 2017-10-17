/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef JSICASEHECKER_H
#define JSICASEHECKER_H

#include <memory>
#include <vector>

namespace analyzer {
  namespace checker {
    class SyntaxCheckerParent;
    class JSICaseChecker
    {
    public:
      JSICaseChecker() = delete;
      explicit JSICaseChecker(SyntaxCheckerParent * parent);
      ~JSICaseChecker();
      bool HasData() const;
      void SetData(const std::shared_ptr<std::vector<unsigned char>> & data);
      void ReleaseData();

      bool IsMyCase(const size_t & offset);

    protected:
      static bool hasPreByte(const size_t & offset);
      static bool isByteSpace(const size_t & offset, const std::shared_ptr<std::vector<unsigned char>> & data);
      static bool isByteSpace(const unsigned char & byte);
      static bool isByteBeforeSpace(const size_t & offset, const std::shared_ptr<std::vector<unsigned char>> & data);
      static bool isByteBeforeLineFeed(const size_t & offset, const std::shared_ptr<std::vector<unsigned char>> & data);
      static unsigned char findNextNoneSpacePrintable(const size_t & offset, const std::shared_ptr<std::vector<unsigned char>> & data);
      static std::string findWordBeforeOffset(const size_t numWordsBefore, const size_t & offset, const std::shared_ptr<std::vector<unsigned char>> & data);
      static bool lastByteInLineIs(const unsigned char value, const size_t & offset, const std::shared_ptr<std::vector<unsigned char>> & data);
      static std::vector<unsigned char> getRestOfLineWithoutLF(const size_t & offset, const std::shared_ptr<std::vector<unsigned char>> & data, const bool & skipSpaces);
      static bool isNoneSpacePrintable(const unsigned char & byte);

    private:
      SyntaxCheckerParent * parent;
      std::shared_ptr<std::vector<unsigned char>> data;
      
      bool isIfCase(const size_t & offset);
      bool isImplementsCase(const size_t & offset);
      bool isImportCase(const size_t & offset);

    public:
      static const std::string KeyWord_if;
      static const std::string KeyWord_implements;
      static const std::string KeyWord_import;
    };
  }
}
#endif