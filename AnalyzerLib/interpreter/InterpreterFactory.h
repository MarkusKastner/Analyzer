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
      ~InterpreterFactory();

      static InterpreterFactory * GetInstance();
      std::shared_ptr<Interpreter> CreateInterpreter(const std::shared_ptr<std::vector<unsigned char>> & data);
      std::shared_ptr<Interpreter> CreateInterpreter(const std::shared_ptr<std::vector<unsigned char>> & data, const size_t & indexBegin, const size_t & offset);
      std::shared_ptr<Interpreter> CreateHexInterpreter(const std::shared_ptr<std::vector<unsigned char>> & data);

    private:
      static InterpreterFactory * instance;
      InterpreterFactory();
    };
  }
}
#endif