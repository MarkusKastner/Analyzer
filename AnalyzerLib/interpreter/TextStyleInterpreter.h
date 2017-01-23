/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef TEXTSTYLEINTERPRETER_H
#define TEXTSTYLEINTERPRETER_H

#if _USRDLL
#define IMEX __declspec(dllexport)
#else
#define IMEX __declspec(dllimport)
#endif

#include <memory>

#include "InterpreterDataImpl.h"

namespace analyzer{
  namespace interpreter{
    class IMEX TextStyleInterpreter : public InterpreterDataImpl
    {
    public:
      TextStyleInterpreter();
      explicit TextStyleInterpreter(const std::shared_ptr<analyzer::core::ByteCollection> & byteCollection);
      virtual ~TextStyleInterpreter();

      bool IsXML();

    protected:
      virtual void setFormatter();
    };
  }
}

#endif