/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "BMPInterpreter.h"

namespace analyzer {
  namespace interpreter {
    BMPInterpreter::BMPInterpreter()
      :Interpreter(), data(), text(), fileHeader(), infoHeader(), htmlDoc()
    {
      this->setup();
    }

    BMPInterpreter::BMPInterpreter(const std::shared_ptr<std::vector<unsigned char>>& data)
      : Interpreter(), data(data), text(), fileHeader(), infoHeader(), htmlDoc()
    { 
      this->setup();
      this->readFileData();
    }

    BMPInterpreter::BMPInterpreter(const std::shared_ptr<std::vector<unsigned char>>& data, const size_t & indexBegin, const size_t & offset)
      : Interpreter(indexBegin, offset), data(data), text(), fileHeader(), infoHeader(), htmlDoc()
    {
    }

    BMPInterpreter::~BMPInterpreter()
    {
    }

    bool BMPInterpreter::HasData()
    {
      return !(!data);
    }

    void BMPInterpreter::SetData(const std::shared_ptr<std::vector<unsigned char>>& data)
    {
      this->data = data;
      this->readFileData();
    }

    void BMPInterpreter::SetData(const std::shared_ptr<std::vector<unsigned char>>& data, const size_t & indexBegin, const size_t & offset)
    {
      this->setLimits(indexBegin, offset);
      this->SetData(data);
    }

    bool BMPInterpreter::UseRichText()
    {
      return true;
    }

    const std::string & BMPInterpreter::GetText()
    {
      this->createHTMLDoc();
      this->text = this->htmlDoc.GetString();
      return this->text;
    }

    core::FileFormat BMPInterpreter::GetFileFormat()
    {
      return core::FileFormat::bmp;
    }

    const BMPInterpreter::FileHeader & BMPInterpreter::GetFileHeader() const
    {
      return this->fileHeader;
    }

    const BMPInterpreter::InfoHeader & BMPInterpreter::GetInfoHeader() const
    {
      return this->infoHeader;
    }

    void BMPInterpreter::readFileData()
    {
      this->readFileHeader();
      this->readInfoHeader();
    }

    void BMPInterpreter::readFileHeader()
    {
      size_t indexBegin = this->getIndexBegin();
      size_t offset = this->data->size();

      if (this->hasLimits()) {
        offset = this->getOffset();
      }

      if (offset < minimumFileSize) {
        throw InterpreterException("Data size too small to be a bitmap");
      }
      this->fileHeader.Type = Interpreter::toASCII(this->data, 0, 2);
      this->fileHeader.FileSize = *reinterpret_cast<const uint32_t*>(&this->data->at(indexBegin + 2));
      this->fileHeader.Reserved1 = *reinterpret_cast<const uint16_t*>(&this->data->at(indexBegin + 6));
      this->fileHeader.Reserved2 = *reinterpret_cast<const uint16_t*>(&this->data->at(indexBegin + 8));
      this->fileHeader.InfoOffset = *reinterpret_cast<const uint32_t*>(&this->data->at(indexBegin + 10));
    }

    void BMPInterpreter::readInfoHeader()
    {
      size_t indexBegin = this->getIndexBegin();
      this->infoHeader.SizeInfoHeader = *reinterpret_cast<const uint32_t*>(&this->data->at(indexBegin + 14));
      this->infoHeader.Width = *reinterpret_cast<const int32_t*>(&this->data->at(indexBegin + 18));
      this->infoHeader.Height = *reinterpret_cast<const int32_t*>(&this->data->at(indexBegin + 22));
      this->infoHeader.FormerNumberOfColorLayers = *reinterpret_cast<const uint16_t*>(&this->data->at(indexBegin + 26));
      this->infoHeader.BitCount = *reinterpret_cast<const uint16_t*>(&this->data->at(indexBegin + 28));
      this->infoHeader.CompressionFormat = static_cast<Compression>(*reinterpret_cast<const uint32_t*>(&this->data->at(indexBegin + 30)));
      this->infoHeader.ImageSize = *reinterpret_cast<const uint32_t*>(&this->data->at(indexBegin + 34));
      this->infoHeader.PixPerMeterX = *reinterpret_cast<const int32_t*>(&this->data->at(indexBegin + 38));
      this->infoHeader.PixPerMeterY = *reinterpret_cast<const int32_t*>(&this->data->at(indexBegin + 42));
      this->infoHeader.NumColorsInTable = *reinterpret_cast<const uint32_t*>(&this->data->at(indexBegin + 46));
      this->infoHeader.NumUsedColorsInPic = *reinterpret_cast<const uint32_t*>(&this->data->at(indexBegin + 50));
    }

    void BMPInterpreter::setup()
    {
      this->htmlDoc.SetTitle("Windows Bitmap");
    }

    void BMPInterpreter::createHTMLDoc()
    {
      this->htmlDoc.AddHeading(HTML::Heading("Windows Bitmap", 1));
      this->htmlDoc.AddHeading(HTML::Heading("File Header", 2));
      this->htmlDoc.AddTable(this->createFileHeaderTable());
      this->htmlDoc.AddLineFeed();
      this->htmlDoc.AddHeading(HTML::Heading("Info Header", 2));
      this->htmlDoc.AddTable(this->createInfoHeaderTable());
      this->htmlDoc.AddLineFeed();
    }

    HTML::Table BMPInterpreter::createFileHeaderTable()
    {
      std::vector<std::string> header;
      header.push_back("Value");
      header.push_back("Content");

      std::vector<std::string> typeLine;
      typeLine.push_back(this->fileHeader.Type);
      typeLine.push_back("ASCII signature declaring the type of data. In most cases \'BM\'.");

      std::vector<std::string> sizeLine;
      sizeLine.push_back(std::to_string(this->fileHeader.FileSize));
      sizeLine.push_back("Size of the file (unreliable)");

      std::vector<std::string> res1Line;
      res1Line.push_back(std::to_string(this->fileHeader.Reserved1));
      res1Line.push_back("Reserved - could be used by different programs, but is normally 0");

      std::vector<std::string> res2Line;
      res2Line.push_back(std::to_string(this->fileHeader.Reserved2));
      res2Line.push_back("Reserved - could be used by different programs, but is normally 0");

      std::vector<std::string> offsetLine;
      offsetLine.push_back(std::to_string(this->fileHeader.InfoOffset));
      offsetLine.push_back("Offset to picture data");

      HTML::Table table;
      table.SetHeader(header);
      table.AddLine(typeLine);
      table.AddLine(sizeLine);
      table.AddLine(res1Line);
      table.AddLine(res2Line);
      table.AddLine(offsetLine);

      return table;
    }

    HTML::Table BMPInterpreter::createInfoHeaderTable()
    {
      std::vector<std::string> header;
      header.push_back("Value");
      header.push_back("Content");

      std::vector<std::string> lineHederSize;
      lineHederSize.push_back(std::to_string(this->infoHeader.SizeInfoHeader));
      lineHederSize.push_back("Size of the Info Header in bytes.");

      std::vector<std::string> lineW;
      lineW.push_back(std::to_string(this->infoHeader.Width));
      lineW.push_back("Image width");

      std::vector<std::string> lineH;
      lineH.push_back(std::to_string(this->infoHeader.Height));
      lineH.push_back("Image height");

      std::vector<std::string> lineColLayers;
      lineColLayers.push_back(std::to_string(this->infoHeader.FormerNumberOfColorLayers));
      lineColLayers.push_back("Number of color layers (not used in newer versions and shoult be 1)");

      std::vector<std::string> lineBitCount;
      lineBitCount.push_back(std::to_string(this->infoHeader.BitCount));
      lineBitCount.push_back("Bits per pixel 1, 4, 8, 16, 24 or 32");

      std::vector<std::string> lineCompression;
      switch (this->infoHeader.CompressionFormat) {
      case Compression::Uncompressed:
        lineCompression.push_back("BI_RGB");
        lineCompression.push_back("Uncompressed");
        break;
      case Compression::RLE8:
        lineCompression.push_back("BI_RLE8");
        lineCompression.push_back("Run-length encoding 8 bit/pixel");
        break;
      case Compression::RLE4:
        lineCompression.push_back("BI_RLE4");
        lineCompression.push_back("Run-length encoding 4 bit/pixel");
        break;
      case Compression::Bitfields:
        lineCompression.push_back("BI_BITFIELDS");
        lineCompression.push_back("Unkompressed and defines by color mask (only for 16 an 32 bit)");
        break;
      }

      std::vector<std::string> lineImgSize;
      lineImgSize.push_back(std::to_string(this->infoHeader.ImageSize));
      lineImgSize.push_back("Size of image in byte.");

      std::vector<std::string> linePPMX;
      linePPMX.push_back(std::to_string(this->infoHeader.PixPerMeterX));
      linePPMX.push_back("Horzontal resolution in pixel per meter.");

      std::vector<std::string> linePPMY;
      linePPMY.push_back(std::to_string(this->infoHeader.PixPerMeterY));
      linePPMY.push_back("Vertical resolution in pixel per meter.");

      std::vector<std::string> lineNumCol;
      lineNumCol.push_back(std::to_string(this->infoHeader.NumColorsInTable));
      lineNumCol.push_back("0 if bit count is 1,\number of entries in color table if bit count is 4 or 8 (in this case 0 means maximum entries),\nin other cases the number of entries in color table, to serve as hint (0 means, no color table)");

      std::vector<std::string> lineUsedCol;
      lineUsedCol.push_back(std::to_string(this->infoHeader.NumUsedColorsInPic));
      lineUsedCol.push_back("If bit count 1, 4 or 8, the number of colors in the picture, else the numbers of coors in the color table, if non exists the value is 0.");

      HTML::Table table;
      table.SetHeader(header);
      table.AddLine(lineHederSize);
      table.AddLine(lineW);
      table.AddLine(lineH);
      table.AddLine(lineColLayers);
      table.AddLine(lineBitCount);
      table.AddLine(lineCompression);
      table.AddLine(lineImgSize);
      table.AddLine(linePPMX);
      table.AddLine(linePPMY);
      table.AddLine(lineNumCol);
      table.AddLine(lineUsedCol);
      return table;
    }
  }
}