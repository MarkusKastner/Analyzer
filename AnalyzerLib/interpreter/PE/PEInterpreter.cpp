#include "PEInterpreter.h"

#include <Windows.h>

#include <bitset>

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

      if (dataSize < sizeof(PEInterpreter::DOSHeader)) {
        return;
      }

      memcpy(&this->dosHeader, this->data.get()->data(), sizeof(PEInterpreter::DOSHeader));

      if (dataSize < this->dosHeader.PEOffset + PEInterpreter::SizeOfNTSignature) {
        return;
      }

      unsigned int coffHeaderOffset = this->dosHeader.PEOffset + PEInterpreter::SizeOfNTSignature;
      memcpy(&this->coffHeader, this->data.get()->data() + coffHeaderOffset, sizeof(PEInterpreter::COFFHeader));

      unsigned int peOptionalHeaderOffset = coffHeaderOffset + sizeof(PEInterpreter::COFFHeader);
      memcpy(&this->peHeader, this->data.get()->data() + peOptionalHeaderOffset, sizeof(PEInterpreter::PEOptionalHeader));

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
      std::vector<std::string> header;
      header.push_back("Element");
      header.push_back("Value");

      HTML::Table table;
      table.SetHeader(header);

      table.AddLine(this->coffMachine2Line());
      table.AddLine(this->coffNumbSections2Line());
      table.AddLine(this->coffTimeDateStamp2Line());
      table.AddLine(this->coffPointerToSymbolTable2Line());
      table.AddLine(this->coffNumOfSymbols2Line());
      table.AddLine(this->coffSizeOfOptionalHeader2Line());
      table.AddLine(this->coffCharacteristics2Line());

      return table;
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

    std::vector<std::string> PEInterpreter::coffMachine2Line()
    {
      std::vector<std::string> line;
      line.push_back("Machine");
      switch (this->coffHeader.Machine) {
      case 0x14c:	
        line.push_back("Intel 386"); 
        break;
      case 0x8664:	
        line.push_back("x64"); 
        break;
      case 0x162:	
        line.push_back("MIPS R3000"); 
        break;
      case 0x168:	
        line.push_back("MIPS R10000");
        break;
      case 0x169:	
        line.push_back("MIPS little endian WCI v2"); 
        break;
      case 0x183:	
        line.push_back("old Alpha AXP"); 
        break;
      case 0x184:	
        line.push_back("Alpha AXP"); 
        break;
      case 0x1a2:	
        line.push_back("Hitachi SH3"); 
        break;
      case 0x1a3:	
        line.push_back("Hitachi SH3 DSP"); 
        break;
      case 0x1a6:	
        line.push_back("Hitachi SH4"); 
        break;
      case 0x1a8:	
        line.push_back("Hitachi SH5"); 
        break;
      case 0x1c0:	
        line.push_back("ARM little endian"); 
        break;
      case 0x1c2:	
        line.push_back("Thumb"); 
        break;
      case 0x1d3:	
        line.push_back("Matsushita AM33"); 
        break;
      case 0x1f0:	
        line.push_back("PowerPC little endian"); 
        break;
      case 0x1f1:	
        line.push_back("PowerPC with floating point support"); 
        break;
      case 0x200:	
        line.push_back("Intel IA64"); 
        break;
      case 0x266:	
        line.push_back("MIPS16"); 
        break;
      case 0x268:	
        line.push_back("Motorola 68000 series"); 
        break;
      case 0x284:	
        line.push_back("Alpha AXP 64 - bit"); 
        break;
      case 0x366:	
        line.push_back("MIPS with FPU"); 
        break;
      case 0x466:	
        line.push_back("MIPS16 with FPU"); 
        break;
      case 0xebc:	
        line.push_back("EFI Byte Code"); 
        break;
      case 0x9041:	
        line.push_back("Mitsubishi M32R little endian"); 
        break;
      case 0xc0ee:	
        line.push_back("clr pure MSIL"); 
        break;
      default:
        line.push_back("unknown");
      }
      return line;
    }

    std::vector<std::string> PEInterpreter::coffNumbSections2Line()
    {
      std::vector<std::string> line;
      line.push_back("Number of sections");
      line.push_back(std::to_string(this->coffHeader.NumbSections));
      return line;
    }

    std::vector<std::string> PEInterpreter::coffTimeDateStamp2Line()
    {
      std::vector<std::string> line;
      line.push_back("Timestamp");
      line.push_back(std::to_string(this->coffHeader.TimeDateStamp));
      return line;
    }

    std::vector<std::string> PEInterpreter::coffPointerToSymbolTable2Line()
    {
      std::vector<std::string> line;
      line.push_back("Pointer to symbol table");
      line.push_back(std::to_string(this->coffHeader.PointerToSymbolTable));
      return line;
    }

    std::vector<std::string> PEInterpreter::coffNumOfSymbols2Line()
    {
      std::vector<std::string> line;
      line.push_back("Number of symbols");
      line.push_back(std::to_string(this->coffHeader.NumOfSymbols));
      return line;
    }

    std::vector<std::string> PEInterpreter::coffSizeOfOptionalHeader2Line()
    {
      std::vector<std::string> line;
      line.push_back("Size of optional header");
      line.push_back(std::to_string(this->coffHeader.SizeOfOptionalHeader));
      return line;
    }

    std::vector<std::string> PEInterpreter::coffCharacteristics2Line()
    {
      std::vector<std::string> line;
      line.push_back("Characteristics");

      std::bitset<16> characteristics(this->coffHeader.Characteristics);

      std::string characteristicsString;

      if (characteristics[0]) { characteristicsString += "Relocation information was stripped from file<br>"; }
      if (characteristics[1]) { characteristicsString += "The file is executable<br>"; }
      if (characteristics[2]) { characteristicsString += "COFF line numbers were stripped from file<br>"; }
      if (characteristics[3]) { characteristicsString += "COFF symbol table entries were stripped from file<br>"; }
      if (characteristics[4]) { characteristicsString += "Aggressively trim the working set(obsolete)<br>"; }
      if (characteristics[5]) { characteristicsString += "The application can handle addresses greater than 2 GB<br>"; }
      if (characteristics[7]) { characteristicsString += "The bytes of the word are reversed(obsolete)<br>"; }
      if (characteristics[8]) { characteristicsString += "The computer supports 32 - bit words<br>"; }
      if (characteristics[9]) { characteristicsString += "Debugging information was removed and stored separately in another file<br>"; }
      if (characteristics[10]) { characteristicsString += "If the image is on removable media, copy it to and run it from the swap file<br>"; }
      if (characteristics[11]) { characteristicsString += "If the image is on the network, copy it to and run it from the swap file<br>"; }
      if (characteristics[12]) { characteristicsString += "The image is a system file<br>"; }
      if (characteristics[13]) { characteristicsString += "The image is a DLL file<br>"; }
      if (characteristics[14]) { characteristicsString += "The image should only be ran on a single processor computer<br>"; }
      if (characteristics[15]) { characteristicsString += "The bytes of the word are reversed(obsolete)<br>"; }
      if (characteristicsString.size() > 4) {
        characteristicsString = characteristicsString.substr(0, characteristicsString.size() - 4);
      }
      line.push_back(characteristicsString);
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