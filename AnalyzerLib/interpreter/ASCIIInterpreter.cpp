/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "ASCIIInterpreter.h"

namespace analyzer {
  namespace interpreter {
    ASCIIInterpreter::ASCIIInterpreter()
      :Interpreter(), data(), text()
    {

    }

    ASCIIInterpreter::ASCIIInterpreter(const std::shared_ptr<std::vector<unsigned char>>& data)
      : Interpreter(), data(data), text()
    {
    }

    ASCIIInterpreter::~ASCIIInterpreter()
    {

    }

    bool ASCIIInterpreter::HasData()
    {
      return !(!data);
    }

    void ASCIIInterpreter::SetData(const std::shared_ptr<std::vector<unsigned char>>& data)
    {
      this->data = data;
    }

    const std::string & ASCIIInterpreter::GetText()
    {
      return this->text;
    }

  }
}