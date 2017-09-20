#include "PEInterpreter.h"

#include <Windows.h>

namespace analyzer {
  namespace interpreter {
    PEInterpreter::PEInterpreter()
      :Interpreter(), data(), text(), dosHeader(), peHeader(), htmlDoc()
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

      if (dataSize < sizeof(PEInterpreter::DOSHeader)) {
        return;
      }

      memcpy(&this->dosHeader, this->data.get()->data(), sizeof(PEInterpreter::DOSHeader));

      if (dataSize < this->dosHeader.PEOffset + PEInterpreter::SizeOfNTSignature) {
        return;
      }

      unsigned int peOptionalHeader = this->dosHeader.PEOffset + PEInterpreter::SizeOfNTSignature;
      memcpy(&this->peHeader, this->data.get()->data() + peOptionalHeader, sizeof(PEInterpreter::PEOptionalHeader));

      std::string test;

    }

    void PEInterpreter::createHTMLDoc()
    {
      this->htmlDoc.AddHeading(HTML::Heading("Executable File", 1));
      this->htmlDoc.AddHeading(HTML::Heading("DOS Header", 2));
      this->htmlDoc.AddTable(this->createDOSHeaderTable());
      this->htmlDoc.AddLineFeed();
      this->htmlDoc.AddHeading(HTML::Heading("COFF Header", 2));
      this->htmlDoc.AddTable(this->createCOFFHeaderTable());
      this->htmlDoc.AddLineFeed();
      this->htmlDoc.AddHeading(HTML::Heading("PE Header", 2));
      this->htmlDoc.AddTable(this->createPEHeaderTable());
      this->htmlDoc.AddLineFeed();
    }

    HTML::Table PEInterpreter::createDOSHeaderTable()
    {
      this->dosHeader.MinAlloc;
      this->dosHeader.MaxAlloc;
      this->dosHeader.ss;
      this->dosHeader.sp;
      this->dosHeader.Checksum;
      this->dosHeader.ip;
      this->dosHeader.cs;
      this->dosHeader.relocpos;
      this->dosHeader.noverlay;
      this->dosHeader.Reserved1[4];
      this->dosHeader.OEMID;
      this->dosHeader.OEMInfo;
      this->dosHeader.Reserved2[10];
      this->dosHeader.PEOffset;

      std::vector<std::string> header;
      header.push_back("Element");
      header.push_back("Value");

      HTML::Table table;
      table.SetHeader(header);
      table.AddLine(this->dosSignature2Line());
      table.AddLine(this->size2Line());
      table.AddLine(this->numBlocks2Line());
      table.AddLine(this->numRelock2Line());
      table.AddLine(this->sizeInParagraphs2Line());

      return table;
    }

    HTML::Table PEInterpreter::createCOFFHeaderTable()
    {
      return HTML::Table();
    }

    HTML::Table PEInterpreter::createPEHeaderTable()
    {
      std::vector<std::string> header;
      header.push_back("Element");
      header.push_back("Value");

      HTML::Table table;
      table.SetHeader(header);
      table.AddLine(this->peSignature2Line());

      return table;
    }

    std::vector<std::string> PEInterpreter::dosSignature2Line()
    {
      std::string signature;
      signature += this->dosHeader.Signature[0];
      signature += this->dosHeader.Signature[1];

      std::vector<std::string> line;
      line.push_back("Signature");
      line.push_back(signature);
      return line;
    }

    std::vector<std::string> PEInterpreter::size2Line()
    {
      std::vector<std::string> line;
      line.push_back("Bytes on last page");
      line.push_back(std::to_string(this->dosHeader.Lastsize));
      return line;
    }

    std::vector<std::string> PEInterpreter::numBlocks2Line()
    {
      std::vector<std::string> line;
      line.push_back("Number of pages");
      line.push_back(std::to_string(this->dosHeader.NumBlocks));
      return line;
    }

    std::vector<std::string> PEInterpreter::numRelock2Line()
    {
      std::vector<std::string> line;
      line.push_back("Relocations");
      line.push_back(std::to_string(this->dosHeader.NumReloc));
      return line;
    }

    std::vector<std::string> PEInterpreter::sizeInParagraphs2Line()
    {
      std::vector<std::string> line;
      line.push_back("Size of header in paragraphs");
      line.push_back(std::to_string(this->dosHeader.hdrsize));
      return line;
    }

    std::vector<std::string> PEInterpreter::peSignature2Line()
    {
      std::vector<std::string> line;
      line.push_back("Image type");

      if (this->peHeader.Signature == NTX32_Type) {
        line.push_back("32 bit");
      }
      else if (this->peHeader.Signature == NTX64_Type) {
        line.push_back("64 bit");
      }
      else if (this->peHeader.Signature == ROM_Type) {
        line.push_back("ROM");
      }
      else {
        line.push_back("unknown");
      }
      return line;
    }

  }
}