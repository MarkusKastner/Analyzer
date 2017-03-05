/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "XMLInterpreter.h"

namespace analyzer {
  namespace interpreter {
    XMLInterpreter::XMLInterpreter()
      :Interpreter(), data(), text()
    {

    }

    XMLInterpreter::XMLInterpreter(const std::shared_ptr<std::vector<unsigned char>>& data)
      : Interpreter(), data(data), text()
    {
    }

    XMLInterpreter::~XMLInterpreter()
    {
    }

    bool XMLInterpreter::HasData()
    {
      return !(!data);
    }

    void XMLInterpreter::SetData(const std::shared_ptr<std::vector<unsigned char>>& data)
    {
      this->data = data;
    }

    const std::string & XMLInterpreter::GetText()
    {
      return this->text;
    }
  }
}