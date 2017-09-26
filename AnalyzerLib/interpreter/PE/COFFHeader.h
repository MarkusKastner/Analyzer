/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef COFFHEADER_H
#define COFFHEADER_H

#include <bitset>

namespace analyzer {
  namespace interpreter {
    struct COFFHeaderStruct
    {
      short Machine;
      short NumbSections;
      long TimeDateStamp;
      long PointerToSymbolTable;
      long NumOfSymbols;
      short SizeOfOptionalHeader;
      short Characteristics;
    };

    class COFFHeader
    {
    public:
      COFFHeader() {}
      ~COFFHeader() {}

      void SetData(const COFFHeaderStruct & coffheaderStruct) { this->coffHeader = coffheaderStruct; }
      HTML::Table ToTable() {
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

    private:
      COFFHeaderStruct coffHeader;

      std::vector<std::string> coffMachine2Line()
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

      std::vector<std::string> coffNumbSections2Line()
      {
        std::vector<std::string> line;
        line.push_back("Number of sections");
        line.push_back(std::to_string(this->coffHeader.NumbSections));
        return line;
      }

      std::vector<std::string> coffTimeDateStamp2Line()
      {
        std::vector<std::string> line;
        line.push_back("Timestamp");
        line.push_back(std::to_string(this->coffHeader.TimeDateStamp));
        return line;
      }

      std::vector<std::string> coffPointerToSymbolTable2Line()
      {
        std::vector<std::string> line;
        line.push_back("Pointer to symbol table");
        line.push_back(std::to_string(this->coffHeader.PointerToSymbolTable));
        return line;
      }

      std::vector<std::string> coffNumOfSymbols2Line()
      {
        std::vector<std::string> line;
        line.push_back("Number of symbols");
        line.push_back(std::to_string(this->coffHeader.NumOfSymbols));
        return line;
      }

      std::vector<std::string> coffSizeOfOptionalHeader2Line()
      {
        std::vector<std::string> line;
        line.push_back("Size of optional header");
        line.push_back(std::to_string(this->coffHeader.SizeOfOptionalHeader));
        return line;
      }

      std::vector<std::string> coffCharacteristics2Line()
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
    };
  }
}
#endif