/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef PEINTERPRETER_H
#define PEINTERPRETER_H

#include "AnalyzerLib\interpreter\Interpreter.h"
#include "AnalyzerLib\interpreter\HTML\Document.h"

namespace analyzer {
  namespace interpreter {
    class PEInterpreter : public Interpreter
    {
    public:
      struct DOSHeader
      {
        char Signature[2];
        short Lastsize;
        short NumBlocks;
        short NumReloc;
        short hdrsize;
        short MinAlloc;
        unsigned short MaxAlloc;
        short ss;
        short sp;
        short Checksum;
        short ip;
        short cs;
        short relocpos;
        short noverlay;
        short Reserved1[4];
        short OEMID;
        short OEMInfo;
        unsigned short Reserved2[10];
        long  PEOffset;
      };

      struct COFFHeader
      {
        short Machine;
        short NumbSections;
        long TimeDateStamp;
        long PointerToSymbolTable;
        long NumOfSymbols;
        short SizeOfOptionalHeader;
        short Characteristics;
      };

      struct data_directory
      {
        long VirtualAddress;
        long Size;
      };

      struct PEOptionalHeader
      {
        short Signature;
        char MajorLinkerVersion;
        char MinorLinkerVersion;
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
        short Subsystem;
        short DLLCharacteristics;
        long SizeOfStackReserve;
        long SizeOfStackCommit;
        long SizeOfHeapReserve;
        long SizeOfHeapCommit;
        long LoaderFlags;
        long NumberOfRvaAndSizes;
        data_directory * DataDirectory[];
      };

      PEInterpreter();
      explicit PEInterpreter(const std::shared_ptr<std::vector<unsigned char>> & data);
      explicit PEInterpreter(const std::shared_ptr<std::vector<unsigned char>> & data, const size_t & indexBegin, const size_t & offset);
      virtual ~PEInterpreter();

      virtual bool HasData();
      virtual void SetData(const std::shared_ptr<std::vector<unsigned char>> & data);
      virtual void SetData(const std::shared_ptr<std::vector<unsigned char>> & data, const size_t & indexBegin, const size_t & offset);
      virtual bool UseRichText();

      virtual const std::string & GetText();
      virtual core::FileFormat GetFileFormat();

    private:
      std::shared_ptr<std::vector<unsigned char>> data;
      std::string text;
      DOSHeader dosHeader;

      void interpret();
    };
  }
}
#endif