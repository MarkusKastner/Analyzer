/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "ASCIIInterpreter.h"

namespace analyzer {
  namespace interpreter {
    ASCIIInterpreter::ASCIIInterpreter()
      :Interpreter(), data(), text()
    {

    }

    ASCIIInterpreter::ASCIIInterpreter(const std::shared_ptr<std::vector<unsigned char>>& data)
      : Interpreter(), data(data), text()
    {
    }

    ASCIIInterpreter::ASCIIInterpreter(const std::shared_ptr<std::vector<unsigned char>>& data, const size_t & indexBegin, const size_t & offset)
      : Interpreter(indexBegin, offset), data(data), text()
    {
    }

    ASCIIInterpreter::~ASCIIInterpreter()
    {

    }

    bool ASCIIInterpreter::HasData()
    {
      return !(!data);
    }

    void ASCIIInterpreter::SetData(const std::shared_ptr<std::vector<unsigned char>>& data)
    {
      this->data = data;
    }

    void ASCIIInterpreter::SetData(const std::shared_ptr<std::vector<unsigned char>>& data, const size_t & indexBegin, const size_t & offset)
    {
      this->setLimits(indexBegin, offset);
      this->SetData(data);
    }

    const std::string & ASCIIInterpreter::GetText()
    {
      size_t offset = this->data->size();
      if (this->hasLimits()) {
        offset = this->getOffset();
      }
      this->text = Interpreter::toASCII(this->data, this->getIndexBegin(), offset);
      return this->text;
    }

    core::FileFormat ASCIIInterpreter::GetFileFormat()
    {
      return core::FileFormat::ascii;
    }

  }
}