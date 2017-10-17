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
      static bool isByteBeforeSpace(const size_t & offset, const std::shared_ptr<std::vector<unsigned char>> & data);
      static unsigned char findNextNoneSpacePrintable(const size_t & offset, const std::shared_ptr<std::vector<unsigned char>> & data);
      static bool isNoneSpacePrintable(const unsigned char & byte);

    private:
      SyntaxCheckerParent * parent;
      std::shared_ptr<std::vector<unsigned char>> data;
      
      bool isIfCase(const size_t & offset);
      bool isImplementsCase(const size_t & offset);

    public:
      static const std::string KeyWord_if;
      static const std::string KeyWord_implements;
    };
  }
}
#endif