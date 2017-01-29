/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef TEXTSTYLEINTERPRETER_H
#define TEXTSTYLEINTERPRETER_H

#include <memory>
#include <vector>

#include "InterpreterDataImpl.h"

namespace analyzer{
  namespace interpreter{
    class TextStyleInterpreter : public InterpreterDataImpl
    {
    public:
      TextStyleInterpreter();
      explicit TextStyleInterpreter(const std::shared_ptr<std::vector<unsigned char>> & data);
      virtual ~TextStyleInterpreter();

      bool IsXML();

    protected:
      virtual void setFormatter();
    };
  }
}

#endif