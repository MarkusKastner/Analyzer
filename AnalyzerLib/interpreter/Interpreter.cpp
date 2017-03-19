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

    void Interpreter::SetObserver(InterpreterObserver * observer)
    {
      this->observer = observer;
    }

    void Interpreter::DoSpecialProcessing()
    {
    }

    void Interpreter::AddInternalFile(const std::shared_ptr<core::File>& internalFile)
    {
      if (this->observer != nullptr) {
        this->observer->AddInternalFile(internalFile);
      }
    }

    Interpreter::Interpreter()
      :indexBegin(0), offset(0), observer(nullptr)
    {
    }

    Interpreter::Interpreter(const size_t & indexBegin, const size_t & offset)
      :indexBegin(indexBegin), offset(offset), observer(nullptr)
    {
    }

    bool Interpreter::hasLimits()
    {
      if (offset != 0) {
        return true;
      }
      return false;
    }

    void Interpreter::setLimits(const size_t & indexBegin, const size_t & offset)
    {
      this->indexBegin = indexBegin;
      this->offset = offset;
    }

    const size_t & Interpreter::getIndexBegin() const
    {
      return this->indexBegin;
    }

    const size_t & Interpreter::getOffset() const
    {
      return this->offset;
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