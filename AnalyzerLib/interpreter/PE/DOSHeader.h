/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef DOSHEADER_H
#define DOSHEADER_H

namespace analyzer {
  namespace interpreter {
    struct DOSHeaderStruct
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
      long PEOffset;
    };

    class DOSHeader
    {
    public:
      DOSHeader() :dosHeader() {}
      ~DOSHeader() {}

      const long & GetPEOffset() const { return this->dosHeader.PEOffset; }
      void SetData(const DOSHeaderStruct & dosHeaderStruct) { this->dosHeader = dosHeaderStruct; }
      HTML::Table ToTable() {
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

    private:
      DOSHeaderStruct dosHeader;

      std::vector<std::string> dosSignature2Line()
      {
        std::string signature;
        signature += this->dosHeader.Signature[0];
        signature += this->dosHeader.Signature[1];

        std::vector<std::string> line;
        line.push_back("Signature");
        line.push_back(signature);
        return line;
      }

      std::vector<std::string> size2Line()
      {
        std::vector<std::string> line;
        line.push_back("Bytes on last page");
        line.push_back(std::to_string(this->dosHeader.Lastsize));
        return line;
      }

      std::vector<std::string> numBlocks2Line()
      {
        std::vector<std::string> line;
        line.push_back("Number of pages");
        line.push_back(std::to_string(this->dosHeader.NumBlocks));
        return line;
      }

      std::vector<std::string> numRelock2Line()
      {
        std::vector<std::string> line;
        line.push_back("Relocations");
        line.push_back(std::to_string(this->dosHeader.NumReloc));
        return line;
      }

      std::vector<std::string> sizeInParagraphs2Line()
      {
        std::vector<std::string> line;
        line.push_back("Size of header in paragraphs");
        line.push_back(std::to_string(this->dosHeader.hdrsize));
        return line;
      }
    };
  }
}
#endif