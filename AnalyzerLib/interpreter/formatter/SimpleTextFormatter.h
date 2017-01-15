/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef SIMPLETEXTFORMATTER_H
#define SIMPLETEXTFORMATTER_H

#include "Formatter.h"

namespace analyzer{
  namespace interpreter{
    class SimpleTextFormatter : public Formatter
    {
    public:
      SimpleTextFormatter();
      virtual ~SimpleTextFormatter();

      virtual std::shared_ptr<std::wstring> GetText();

    };
  }
}

#endif