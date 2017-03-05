/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef BMPINTERPRETER_H
#define BMPINTERPRETER_H

#include "Interpreter.h"
#include "AnalyzerLib\interpreter\HTML\Document.h"

namespace analyzer {
  namespace interpreter {
    class BMPInterpreter : public Interpreter
    {
    public:
      static const size_t headerSize = 14;
      static const size_t minimumFileSize = 54;

      BMPInterpreter();
      explicit BMPInterpreter(const std::shared_ptr<std::vector<unsigned char>> & data);
      virtual ~BMPInterpreter();

      virtual bool HasData();
      virtual void SetData(const std::shared_ptr<std::vector<unsigned char>> & data);
      virtual bool UseRichText();

      virtual const std::string & GetText();

      enum Compression 
      {
        Uncompressed  = 0,
        RLE8,
        RLE4,
        Bitfields
      };

      struct FileHeader
      {
        std::string Type;
        uint32_t FileSize;
        uint32_t Reserved1;
        uint32_t Reserved2;
        uint32_t InfoOffset;
      };

      struct InfoHeader
      {
        uint32_t SizeInfoHeader;
        int32_t Width;
        int32_t Height;
        uint16_t FormerNumberOfColorLayers;
        uint16_t BitCount;
        Compression CompressionFormat;
        uint32_t ImageSize;
        int32_t PixPerMeterX;
        int32_t PixPerMeterY;
        uint32_t NumColorsInTable;
        uint32_t NumUsedColorsInPic;
      };

      const FileHeader & GetFileHeader() const;
      const InfoHeader & GetInfoHeader() const;

    private:
      std::shared_ptr<std::vector<unsigned char>> data;
      std::string text;
      FileHeader fileHeader;
      InfoHeader infoHeader;
      HTML::Document htmlDoc;

      void readFileData();
      void readFileHeader();
      void readInfoHeader();

      void setup();
    };
  }
}

#endif