/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef BITFORMATTER_H
#define BITFORMATTER_H

#include "Formatter.h"

#include <memory>
#include <string>

namespace analyzer{
  namespace interpreter{
    class BitFormatter : public Formatter
    {
    public:
      BitFormatter();
      explicit BitFormatter(const std::shared_ptr<std::vector<unsigned char>> & data);
      virtual ~BitFormatter();

      virtual std::shared_ptr<std::wstring> GetText();

    private:
      std::string make3Digit(const unsigned char & byte);
    };
  }
}
#endif