/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef PEINTERPRETER_H
#define PEINTERPRETER_H

#include "AnalyzerLib\interpreter\Interpreter.h"
#include "AnalyzerLib\interpreter\HTML\Document.h"

#include "PEOptionalHeader.h"
#include "COFFHeader.h"
#include "DOSHeader.h"

namespace analyzer {
  namespace interpreter {
    class PEInterpreter : public Interpreter
    {
    public:

      static const unsigned int SizeOfNTSignature = 4;

      struct data_directory
      {
        long VirtualAddress;
        long Size;
      };

      PEInterpreter();
      explicit PEInterpreter(const std::shared_ptr<std::vector<unsigned char>> & data);
      explicit PEInterpreter(const std::shared_ptr<std::vector<unsigned char>> & data, const size_t & indexBegin, const size_t & offset);
      virtual ~PEInterpreter();

      virtual bool HasData();
      virtual void SetData(const std::shared_ptr<std::vector<unsigned char>> & data);
      virtual void SetData(const std::shared_ptr<std::vector<unsigned char>> & data, const size_t & indexBegin, const size_t & offset);
      virtual bool UseRichText();

      virtual const std::string & GetText();
      virtual core::FileFormat GetFileFormat();

    private:
      std::shared_ptr<std::vector<unsigned char>> data;
      std::string text;
      DOSHeader dosHeader;
      COFFHeader coffHeader;
      PEOptionalHeader peHeader;
      HTML::Document htmlDoc;

      void interpret();

      void createHTMLDoc();

    };
  }
}
#endif