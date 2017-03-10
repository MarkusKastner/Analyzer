#include "PDFInterpreter.h"

namespace analyzer {
  namespace interpreter {
    PDFInterpreter::PDFInterpreter()
      :Interpreter(), data(), text()
    {
    }

    PDFInterpreter::PDFInterpreter(const std::shared_ptr<std::vector<unsigned char>>& data)
      : Interpreter(), data(data), text()
    {
    }

    PDFInterpreter::~PDFInterpreter()
    {
    }

    bool PDFInterpreter::HasData()
    {
      return !(!data);
    }

    void PDFInterpreter::SetData(const std::shared_ptr<std::vector<unsigned char>>& data)
    {
      this->data = data;
    }

    const std::string & PDFInterpreter::GetText()
    {
      this->text = Interpreter::toASCII(this->data, 0, this->data->size());
      return this->text;
    }

    core::FileFormat PDFInterpreter::GetFileFormat()
    {
      return core::FileFormat::pdf;
    }
  }
}