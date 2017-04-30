#include "PEInterpreter.h"

namespace analyzer {
  namespace interpreter {
    PEInterpreter::PEInterpreter()
      :Interpreter(), data(), text()
    {
    }

    PEInterpreter::PEInterpreter(const std::shared_ptr<std::vector<unsigned char>>& data)
      :Interpreter(), data(data), text()
    {
    }

    PEInterpreter::PEInterpreter(const std::shared_ptr<std::vector<unsigned char>>& data, const size_t & indexBegin, const size_t & offset)
      :Interpreter(indexBegin, offset), data(data), text()
    {
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
  }
}