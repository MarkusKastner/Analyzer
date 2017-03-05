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

    bool BMPInterpreter::UseRichText()
    {
      return true;
    }

    const std::string & BMPInterpreter::GetText()
    {
      this->htmlDoc.AddHeading(HTML::Heading("Windows Bitmap", 1));
      this->text = this->htmlDoc.GetString();
      return this->text;
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
      if (this->data->size() < minimumFileSize) {
        throw InterpreterException("Data size too small to be a bitmap");
      }

      this->fileHeader.Type = Interpreter::toASCII(this->data, 0, 2);
      this->fileHeader.FileSize = *reinterpret_cast<const uint32_t*>(&this->data->at(2));
      this->fileHeader.Reserved1 = *reinterpret_cast<const uint16_t*>(&this->data->at(6));
      this->fileHeader.Reserved2 = *reinterpret_cast<const uint16_t*>(&this->data->at(8));
      this->fileHeader.InfoOffset = *reinterpret_cast<const uint32_t*>(&this->data->at(10));      
    }

    void BMPInterpreter::readInfoHeader()
    {
      this->infoHeader.SizeInfoHeader = *reinterpret_cast<const uint32_t*>(&this->data->at(14));
      this->infoHeader.Width = *reinterpret_cast<const int32_t*>(&this->data->at(18));
      this->infoHeader.Height = *reinterpret_cast<const int32_t*>(&this->data->at(22));
      this->infoHeader.FormerNumberOfColorLayers = *reinterpret_cast<const uint16_t*>(&this->data->at(26));
      this->infoHeader.BitCount = *reinterpret_cast<const uint16_t*>(&this->data->at(28));
      this->infoHeader.CompressionFormat = static_cast<Compression>(*reinterpret_cast<const uint32_t*>(&this->data->at(30)));
      this->infoHeader.ImageSize = *reinterpret_cast<const uint32_t*>(&this->data->at(34));
      this->infoHeader.PixPerMeterX = *reinterpret_cast<const int32_t*>(&this->data->at(38));
      this->infoHeader.PixPerMeterY = *reinterpret_cast<const int32_t*>(&this->data->at(42));
      this->infoHeader.NumColorsInTable = *reinterpret_cast<const uint32_t*>(&this->data->at(46));
      this->infoHeader.NumUsedColorsInPic = *reinterpret_cast<const uint32_t*>(&this->data->at(50));
    }

    void BMPInterpreter::setup()
    {
      this->htmlDoc.SetTitle("Windows Bitmap");
    }
  }
}