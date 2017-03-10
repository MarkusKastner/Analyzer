/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef PDFINTERPRETER_H
#define PDFINTERPRETER_H

#include "Interpreter.h"

namespace analyzer {
  namespace interpreter {
    class PDFInterpreter : public Interpreter
    {
    public:
      PDFInterpreter();
      explicit PDFInterpreter(const std::shared_ptr<std::vector<unsigned char>> & data);
      virtual ~PDFInterpreter();

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