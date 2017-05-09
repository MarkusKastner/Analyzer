#include "PEInterpreter.h"

namespace analyzer {
  namespace interpreter {
    PEInterpreter::PEInterpreter()
      :Interpreter(), data(), text(), dosHeader()
    {
    }

    PEInterpreter::PEInterpreter(const std::shared_ptr<std::vector<unsigned char>>& data)
      :Interpreter(), data(data), text(), dosHeader()
    {
      this->interpret();
    }

    PEInterpreter::PEInterpreter(const std::shared_ptr<std::vector<unsigned char>>& data, const size_t & indexBegin, const size_t & offset)
      :Interpreter(indexBegin, offset), data(data), text(), dosHeader()
    {
      this->interpret();
    }

    PEInterpreter::~PEInterpreter()
    {
    }

    bool PEInterpreter::HasData()
    {
      return false;
    }

    void PEInterpreter::SetData(const std::shared_ptr<std::vector<unsigned char>>& data)
    {
      this->data = data;
      this->interpret();
    }

    void PEInterpreter::SetData(const std::shared_ptr<std::vector<unsigned char>>& data, const size_t & indexBegin, const size_t & offset)
    {
      this->setLimits(indexBegin, offset);
      this->SetData(data);
    }

    bool PEInterpreter::UseRichText()
    {
      return false;
    }

    const std::string & PEInterpreter::GetText()
    {
      return this->text;
    }

    core::FileFormat PEInterpreter::GetFileFormat()
    {
      return core::FileFormat::winExec;
    }

    void PEInterpreter::interpret()
    {
      if (!this->data) {
        return;
      }

      size_t dataSize = this->data->size();
      if (this->getOffset() != 0 && this->getOffset() < dataSize) {
        dataSize = this->getOffset();
      }

      if (dataSize < sizeof(PEInterpreter::DOSHeader)) {
        return;
      }

      memcpy(&this->dosHeader, this->data.get()->data(), sizeof(PEInterpreter::DOSHeader));

      if (dataSize < this->dosHeader.PEOffset + 4) {
        return;
      }


      std::string test;

    }
  }
}