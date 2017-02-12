/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "InterpreterFactory.h"
#include "ASCIIInterpreter.h"

namespace analyzer {
  namespace interpreter {
    InterpreterFactory::InterpreterFactory()
    {
    }

    InterpreterFactory::~InterpreterFactory()
    {
    }

    InterpreterFactory * InterpreterFactory::GetInstance()
    {
      if (nullptr == InterpreterFactory::instance) {
        InterpreterFactory::instance = new InterpreterFactory();
      }
      return nullptr;
    }

    std::shared_ptr<Interpreter> InterpreterFactory::CreateInterpreter(const std::shared_ptr<std::vector<unsigned char>>& data)
    {
      if (data) {
        return std::shared_ptr<Interpreter>(new ASCIIInterpreter(data));
      }
      return std::shared_ptr<Interpreter>();
    }

    InterpreterFactory * InterpreterFactory::instance = nullptr;
  }
}