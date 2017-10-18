/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef JSFCASEHECKER_H
#define JSFCASEHECKER_H

#include <memory>
#include <vector>

namespace analyzer {
  namespace checker {
    class SyntaxCheckerParent;
    class JSFCaseChecker
    {
    public:
      JSFCaseChecker() = delete;
      explicit JSFCaseChecker(SyntaxCheckerParent * parent);
      ~JSFCaseChecker();
      bool HasData() const;
      void SetData(const std::shared_ptr<std::vector<unsigned char>> & data);
      void ReleaseData();

      bool IsMyCase(const size_t & offset);

    private:
      SyntaxCheckerParent * parent;
      std::shared_ptr<std::vector<unsigned char>> data;
      
      bool isForCase(const size_t & offset);

    public:
      static const std::string KeyWord_for;
    };
  }
}
#endif