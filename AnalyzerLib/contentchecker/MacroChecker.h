/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef MACROCHECKER_H
#define MACROCHECKER_H

#include "ContentChecker.h"

namespace analyzer {
  namespace checker {
    class MacroChecker : public ContentChecker
    {
    public:
      MacroChecker();
      virtual ~MacroChecker();

      size_t FindNextSyntaxHint();

    protected:
      virtual void checkData();

    private:
      size_t lastFoundSyntaxOffset;
      bool isSyntax(const size_t & offset);
      bool isICaseSyntax(const size_t & offset);

    public:
      static const std::string KeyWord_if;
      static const std::string KeyWord_implements;
      static const std::string KeyWord_import;
      static const std::string KeyWord_in;
      static const std::string KeyWord_instanceof;
      static const std::string KeyWord_int;
      static const std::string KeyWord_interface;
    };
  }
}
#endif