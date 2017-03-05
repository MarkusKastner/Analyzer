/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <memory>
#include <string>
#include <vector>

#include "AnalyzerLib\base\BaseData.h"
#include "AnalyzerLib\interpreter\error\InterpreterException.h"
namespace analyzer{
  namespace interpreter{
    class Interpreter
    {
    public:
      virtual ~Interpreter() {}

      virtual bool HasData() = 0;
      virtual void SetData(const std::shared_ptr<std::vector<unsigned char>> & data) = 0;
      virtual bool UseRichText();

      virtual const std::string & GetText() = 0;

    protected:
      Interpreter() {}

      static std::string toASCII(const std::shared_ptr<std::vector<unsigned char>> & data, const size_t & index, const size_t & offset);

    };
  }
}
#endif