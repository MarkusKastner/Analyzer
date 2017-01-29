/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef BINARYSTYLEINTERPRETER_H
#define BINARYSTYLEINTERPRETER_H

#include <memory>

#include "InterpreterDataImpl.h"

namespace analyzer{
  namespace interpreter{
    class BinaryStyleInterpreter : public InterpreterDataImpl
    {
    private:
      BinaryStyleInterpreter(const BinaryStyleInterpreter&){}
      BinaryStyleInterpreter & operator=(const BinaryStyleInterpreter&){ return *this; }

    public:
      BinaryStyleInterpreter();
      explicit BinaryStyleInterpreter(const std::shared_ptr<std::vector<unsigned char>> & data);
      virtual ~BinaryStyleInterpreter();

    protected:
      virtual void setFormatter();

    };
  }
}

#endif