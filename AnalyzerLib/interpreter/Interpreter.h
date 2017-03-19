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

#include "AnalyzerLib/base/BaseData.h"
#include "AnalyzerLib/interpreter/error/InterpreterException.h"
#include "AnalyzerLib/core/FileInfo.h"
#include "AnalyzerLib/interpreter/InterpreterObserver.h"

namespace analyzer{
  namespace interpreter{
    class Interpreter
    {
    public:
      virtual ~Interpreter() {}

      virtual bool HasData() = 0;
      virtual void SetData(const std::shared_ptr<std::vector<unsigned char>> & data) = 0;
      virtual void SetData(const std::shared_ptr<std::vector<unsigned char>> & data, const size_t & indexBegin, const size_t & offset) = 0;
      virtual bool UseRichText();

      virtual const std::string & GetText() = 0;
      virtual core::FileFormat GetFileFormat() = 0;
      virtual void SetObserver(InterpreterObserver * observer);
      virtual void DoSpecialProcessing();

      void AddInternalFile(const std::shared_ptr<core::File> & internalFile);

    protected:
      Interpreter();
      explicit Interpreter(const size_t & indexBegin, const size_t & offset);

      bool hasLimits();
      void setLimits(const size_t & indexBegin, const size_t & offset);
      const size_t & getIndexBegin() const;
      const size_t & getOffset() const;

      static std::string toASCII(const std::shared_ptr<std::vector<unsigned char>> & data, const size_t & index, const size_t & offset);

    private:
      size_t indexBegin;
      size_t offset;
      InterpreterObserver * observer;

    };
  }
}
#endif