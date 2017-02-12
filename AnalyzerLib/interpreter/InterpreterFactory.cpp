/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "InterpreterFactory.h"

namespace analyzer {
  namespace interpreter {
    InterpreterFactory::InterpreterFactory()
    {
    }
    InterpreterFactory::~InterpreterFactory()
    {
    }
    Interpreter * InterpreterFactory::CreateInterpreter(const std::shared_ptr<std::vector<unsigned char>>& data)
    {
      return nullptr;
    }
  }
}