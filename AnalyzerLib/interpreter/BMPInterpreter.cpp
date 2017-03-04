/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "BMPInterpreter.h"

namespace analyzer {
  namespace interpreter {
    BMPInterpreter::BMPInterpreter()
      :Interpreter(), data()
    {
    }

    BMPInterpreter::BMPInterpreter(const std::shared_ptr<std::vector<unsigned char>>& data)
      : Interpreter(), data(data)
    {
    }

    BMPInterpreter::~BMPInterpreter()
    {
    }

    bool BMPInterpreter::HasData()
    {
      return !(!data);
    }

    void BMPInterpreter::SetData(const std::shared_ptr<std::vector<unsigned char>>& data)
    {
      this->data = data;
    }
  }
}