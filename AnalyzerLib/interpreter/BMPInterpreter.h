/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef BMPINTERPRETER_H
#define BMPINTERPRETER_H

#include "Interpreter.h"

namespace analyzer {
  namespace interpreter {
    class BMPInterpreter : public Interpreter
    {
    public:
      BMPInterpreter();
      explicit BMPInterpreter(const std::shared_ptr<std::vector<unsigned char>> & data);
      virtual ~BMPInterpreter();

      virtual bool HasData();
      virtual void SetData(const std::shared_ptr<std::vector<unsigned char>> & data);

    private:
      std::shared_ptr<std::vector<unsigned char>> data;
    };
  }
}

#endif