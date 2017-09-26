#include "PEInterpreter.h"

#include <Windows.h>

namespace analyzer {
  namespace interpreter {
    PEInterpreter::PEInterpreter()
      :Interpreter(), data(), text(), dosHeader(), coffHeader(), peHeader(), htmlDoc()
    {
    }

    PEInterpreter::PEInterpreter(const std::shared_ptr<std::vector<unsigned char>>& data)
      :Interpreter(), data(data), text(), dosHeader(), coffHeader(), peHeader(), htmlDoc()
    {
      this->interpret();
    }

    PEInterpreter::PEInterpreter(const std::shared_ptr<std::vector<unsigned char>>& data, const size_t & indexBegin, const size_t & offset)
      :Interpreter(indexBegin, offset), data(data), text(), dosHeader(), coffHeader(), peHeader(), htmlDoc()
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
      return true;
    }

    const std::string & PEInterpreter::GetText()
    {
      this->createHTMLDoc();
      this->text = this->htmlDoc.GetString();
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

      if (dataSize < sizeof(DOSHeaderStruct)) {
        return;
      }

      DOSHeaderStruct dosHeaderStruct;
      memcpy(&dosHeaderStruct, this->data.get()->data(), sizeof(DOSHeaderStruct));
      this->dosHeader.SetData(dosHeaderStruct);

      if (dataSize < this->dosHeader.GetPEOffset() + PEInterpreter::SizeOfNTSignature) {
        return;
      }

      unsigned int coffHeaderOffset = this->dosHeader.GetPEOffset() + PEInterpreter::SizeOfNTSignature;
      COFFHeaderStruct coffheaderStruct;
      memcpy(&coffheaderStruct, this->data.get()->data() + coffHeaderOffset, sizeof(COFFHeaderStruct));
      this->coffHeader.SetData(coffheaderStruct);

      unsigned int peOptionalHeaderOffset = coffHeaderOffset + sizeof(COFFHeaderStruct);
      PEOptionalHeaderStruct peOptionalHeaderStruct;
      memcpy(&peOptionalHeaderStruct, this->data.get()->data() + peOptionalHeaderOffset, sizeof(PEOptionalHeaderStruct));
      this->peHeader.SetData(peOptionalHeaderStruct);

      std::string test;

    }

    void PEInterpreter::createHTMLDoc()
    {
      this->htmlDoc.AddHeading(HTML::Heading("Executable File", 1));
      this->htmlDoc.AddHeading(HTML::Heading("DOS Header", 2));
      this->htmlDoc.AddTable(this->dosHeader.ToTable());
      this->htmlDoc.AddLineFeed();
      this->htmlDoc.AddHeading(HTML::Heading("COFF Header", 2));
      this->htmlDoc.AddTable(this->coffHeader.ToTable());
      this->htmlDoc.AddLineFeed();
      this->htmlDoc.AddHeading(HTML::Heading("PE Header", 2));
      this->htmlDoc.AddTable(this->peHeader.ToTable());
      this->htmlDoc.AddLineFeed();
    }
  }
}