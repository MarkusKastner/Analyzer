/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef ASCIIINTERPRETER_H
#define ASCIIINTERPRETER_H

#include "Interpreter.h"

namespace analyzer {
  namespace interpreter {
    class ASCIIInterpreter : public Interpreter
    {
    public:
      ASCIIInterpreter();
      explicit ASCIIInterpreter(const std::shared_ptr<std::vector<unsigned char>> & data);
      virtual ~ASCIIInterpreter();

      virtual bool HasData();
      virtual void SetData(const std::shared_ptr<std::vector<unsigned char>> & data);
      virtual const std::string & GetText();
      virtual core::FileFormat GetFileFormat();

    private:
      std::shared_ptr<std::vector<unsigned char>> data;
      std::string text;
    };
  }
}

#endif