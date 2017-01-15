/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef BITFORMATTER_H
#define BITFORMATTER_H

#if _USRDLL
#define IMEX __declspec(dllexport)
#else
#define IMEX __declspec(dllimport)
#endif

#include "Formatter.h"

#include <memory>
#include <string>

namespace analyzer{
  namespace interpreter{
    class IMEX BitFormatter : public Formatter
    {
    public:
      BitFormatter();
      virtual ~BitFormatter();

      virtual std::shared_ptr<std::wstring> GetText();

    private:
      std::string make3Digit(const unsigned char & byte);
    };
  }
}
#endif