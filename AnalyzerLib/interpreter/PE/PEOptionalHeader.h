/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef PEOPTIONALHEADER_H
#define PEOPTIONALHEADER_H

namespace analyzer {
  namespace interpreter {
    struct PEOptionalHeaderStruct
    {
      unsigned short Signature;
      unsigned char MajorLinkerVersion;
      unsigned char MinorLinkerVersion;
      long SizeOfCode;
      long SizeOfInitializedData;
      long SizeOfUninitializedData;
      long AddressOfEntryPoint;
      long BaseOfCode;
      long BaseOfData;
      long ImageBase;
      long SectionAlignment;
      long FileAlignment;
      short MajorOSVersion;
      short MinorOSVersion;
      short MajorImageVersion;
      short MinorImageVersion;
      short MajorSubsystemVersion;
      short MinorSubsystemVersion;
      long Win32VersionValue;
      long SizeOfImage;
      long SizeOfHeaders;
      long Checksum;
      unsigned short Subsystem;
      short DLLCharacteristics;
      long SizeOfStackReserve;
      long SizeOfStackCommit;
      long SizeOfHeapReserve;
      long SizeOfHeapCommit;
      long LoaderFlags;
      long NumberOfRvaAndSizes;
      //data_directory * DataDirectory;
    };

    class PEOptionalHeader
    {
    public:

      static const unsigned short NTX32_Type = 0x10b;
      static const unsigned short NTX64_Type = 0x20b;
      static const unsigned short ROM_Type = 0x107;

      PEOptionalHeader() {}
      ~PEOptionalHeader() {}

      void SetData(const PEOptionalHeaderStruct & peOptionalHeaderStruct) { this->peOptionalHeader = peOptionalHeaderStruct; }
      HTML::Table ToTable() {
        std::vector<std::string> header;
        header.push_back("Element");
        header.push_back("Value");

        HTML::Table table;
        table.SetHeader(header);
        table.AddLine(this->peSignature2Line());

        return table;
      }

    private:
      PEOptionalHeaderStruct peOptionalHeader;

      std::vector<std::string> peSignature2Line()
      {
        std::vector<std::string> line;
        line.push_back("Image type");

        if (this->peOptionalHeader.Signature == NTX32_Type) {
          line.push_back("32 bit");
        }
        else if (this->peOptionalHeader.Signature == NTX64_Type) {
          line.push_back("64 bit");
        }
        else if (this->peOptionalHeader.Signature == ROM_Type) {
          line.push_back("ROM");
        }
        else {
          line.push_back("unknown");
        }
        return line;
      }
    };
  }
}
#endif