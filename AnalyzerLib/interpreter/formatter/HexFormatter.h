/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef HEXFORMATTER_H
#define HEXFORMATTER_H

#if _USRDLL
#define IMEX __declspec(dllexport)
#else
#define IMEX __declspec(dllimport)
#endif

#include "Formatter.h"

#include <memory>
#include <string>

namespace analyzer {
  namespace interpreter {
    class IMEX HexFormatter : public Formatter
    {
    public:
      HexFormatter();
      virtual ~HexFormatter();

      virtual std::shared_ptr<std::wstring> GetText();

    private:
      std::wstring * space;
      std::wstring * exp;
      std::wstring * hex;

      void append(const std::shared_ptr<std::wstring> & text);
      std::wstring char2Hex(const unsigned char & value);
      std::wstring char2Expression(const unsigned char & value);
    };
  }
}
#endif