/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef PDFINTERPRETER_H
#define PDFINTERPRETER_H

#include "AnalyzerLib/interpreter/Interpreter.h"
#include "PDFObject.h"

namespace analyzer {
  namespace interpreter {
    class PDFInterpreter : public Interpreter
    {
    public:
      PDFInterpreter();
      explicit PDFInterpreter(const std::shared_ptr<std::vector<unsigned char>> & data);
      explicit PDFInterpreter(const std::shared_ptr<std::vector<unsigned char>> & data, const size_t & indexBegin, const size_t & offset);
      virtual ~PDFInterpreter();

      virtual bool HasData();
      virtual void SetData(const std::shared_ptr<std::vector<unsigned char>> & data);
      virtual void SetData(const std::shared_ptr<std::vector<unsigned char>> & data, const size_t & indexBegin, const size_t & offset);
      virtual const std::string & GetText();
      virtual core::FileFormat GetFileFormat();
      virtual bool UseRichText();
      virtual void DoSpecialProcessing();

      void AddPDFObject(const PDFObject & object);
      PDFObject GetPDFObject(const size_t & number, const size_t & revision);

      void SwitchFolding(const std::string & objectName);

      void CreateObjects();

    private:
      std::shared_ptr<std::vector<unsigned char>> data;
      std::string text;
      std::vector<PDFObject> objects;
      size_t maxIndex;

      size_t findNextObject(const size_t & startIndex);
      size_t findDataOffset(const size_t & startIndex);
      size_t findObjectEndIndex(const size_t & startIndex);
      size_t findPrevLineBreak(const size_t & currentIndex);
      bool offsetsValid(const size_t & dataOffset, const size_t & objectOffset);
      size_t getObjectNumber(const size_t & objectIndex);
      size_t getObjectRevision(const size_t & objectIndex);
      bool isLineBreak(const size_t & index);
      bool isValidSign(const size_t & index);
      bool isEndObject(const size_t & index);

      struct smallerThen {
        inline bool operator() (const PDFObject & obj1, const PDFObject & obj2) {
          return (obj1.GetNumber() < obj2.GetNumber());
        }
      };
    };
  }
}

#endif