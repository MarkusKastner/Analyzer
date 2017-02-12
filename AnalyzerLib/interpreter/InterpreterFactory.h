/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef INTERPRETERFACTORY_H
#define INTERPRETERFACTORY_H

#include <memory>
#include <string>
#include <vector>

namespace analyzer {
  namespace interpreter {
    class Interpreter;
    class InterpreterFactory
    {
    public:
      InterpreterFactory();
      virtual ~InterpreterFactory();

      Interpreter * CreateInterpreter(const std::shared_ptr<std::vector<unsigned char>> & data);
    };
  }
}
#endif