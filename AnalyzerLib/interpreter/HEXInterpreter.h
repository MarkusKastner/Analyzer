/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef HEXINTERPRETER_H
#define HEXINTERPRETER_H

#include "AnalyzerLib/interpreter/Interpreter.h"

#include <string>
#include <vector>

namespace analyzer {
  namespace interpreter {
    class HEXInterpreter : public Interpreter
    {
    public:
      HEXInterpreter();
      explicit HEXInterpreter(const std::shared_ptr<std::vector<unsigned char>> & data);
      explicit HEXInterpreter(const std::shared_ptr<std::vector<unsigned char>> & data, const size_t & indexBegin, const size_t & offset);
      virtual ~HEXInterpreter();

      virtual bool HasData();
      virtual void SetData(const std::shared_ptr<std::vector<unsigned char>> & data);
      virtual void SetData(const std::shared_ptr<std::vector<unsigned char>> & data, const size_t & indexBegin, const size_t & offset);
      virtual const std::string & GetText();
      virtual core::FileFormat GetFileFormat();
      virtual bool UseRichText();

      const std::vector<std::string> & GetHexExpressions();
      std::vector<std::vector<std::string>> GetHexRows();
      std::vector<unsigned char> GetBytesByIndex(const std::vector<size_t> & indexes);

    private:
      std::shared_ptr<std::vector<unsigned char>> data;
      std::vector<std::string> hex;
      std::string text;

      void data2Hex();
      std::string char2Hex(const unsigned char & value);
      size_t findOffset();
    };
  }
}

#endif