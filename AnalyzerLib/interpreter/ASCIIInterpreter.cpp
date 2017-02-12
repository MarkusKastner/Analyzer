/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "ASCIIInterpreter.h"

namespace analyzer {
  namespace interpreter {
    ASCIIInterpreter::ASCIIInterpreter()
      :Interpreter()
    {

    }

    ASCIIInterpreter::~ASCIIInterpreter()
    {

    }

    bool ASCIIInterpreter::HasData()
    {
      return false;
    }

  }
}