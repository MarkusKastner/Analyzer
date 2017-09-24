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

      static const unsigned int SizeOfNTSignature = 4;
      static const unsigned short NTX32_Type = 0x10b;
      static const unsigned short NTX64_Type = 0x20b;
      static const unsigned short ROM_Type = 0x107;

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
      COFFHeader coffHeader;
      PEOptionalHeader peHeader;
      HTML::Document htmlDoc;

      void interpret();

      void createHTMLDoc();
      HTML::Table createDOSHeaderTable();
      HTML::Table createCOFFHeaderTable();
      HTML::Table createPEHeaderTable();

      std::vector<std::string> dosSignature2Line();
      std::vector<std::string> size2Line();
      std::vector<std::string> numBlocks2Line();
      std::vector<std::string> numRelock2Line();
      std::vector<std::string> sizeInParagraphs2Line();

      std::vector<std::string> coffMachine2Line();
      std::vector<std::string> coffNumbSections2Line();
      std::vector<std::string> coffTimeDateStamp2Line();
      std::vector<std::string> coffPointerToSymbolTable2Line();
      std::vector<std::string> coffNumOfSymbols2Line();
      std::vector<std::string> coffSizeOfOptionalHeader2Line();
      std::vector<std::string> coffCharacteristics2Line();

      std::vector<std::string> peSignature2Line();

    };
  }
}
#endif