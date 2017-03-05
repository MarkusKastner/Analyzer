/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "Interpreter.h"

namespace analyzer {
  namespace interpreter {
    bool Interpreter::UseRichText()
    {
      return false;
    }

    std::string Interpreter::toASCII(const std::shared_ptr<std::vector<unsigned char>> & data, const size_t & index, const size_t & offset) 
    {
      if (index + offset > data->size()) {
        throw InterpreterException("Invalid index or offset value in TypeAnalyzer::toASCII()");
      }
      std::string text;
      for (size_t i = index; i < index + offset; ++i) {
        text.push_back(static_cast<char>(data->at(i)));
      }
      return text;
    }
  }
}