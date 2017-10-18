/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef JSVCASEHECKER_H
#define JSVCASEHECKER_H

#include <memory>
#include <vector>

namespace analyzer {
  namespace checker {
    class SyntaxCheckerParent;
    class JSVCaseChecker
    {
    public:
      JSVCaseChecker() = delete;
      explicit JSVCaseChecker(SyntaxCheckerParent * parent);
      ~JSVCaseChecker();
      bool HasData() const;
      void SetData(const std::shared_ptr<std::vector<unsigned char>> & data);
      void ReleaseData();

      bool IsMyCase(const size_t & offset);

    private:
      SyntaxCheckerParent * parent;
      std::shared_ptr<std::vector<unsigned char>> data;
      
      bool isVarCase(const size_t & offset);

    public:
      static const std::string KeyWord_var;
    };
  }
}
#endif