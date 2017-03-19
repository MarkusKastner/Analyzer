/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "TypeAnalyzer.h"

#include "error\CoreException.h"

namespace analyzer {
  namespace core {

    TypeAnalyzer::TypeAnalyzer()
      : indexBegin(0), offset(0)
    {
    }

    TypeAnalyzer::~TypeAnalyzer()
    {
    }

    TypeAnalyzer * TypeAnalyzer::GetInstance()
    {
      if (nullptr == TypeAnalyzer::instance) {
        TypeAnalyzer::instance = new TypeAnalyzer();
      }
      return TypeAnalyzer::instance;
    }

    FileInfo TypeAnalyzer::GetFileInfo(const std::shared_ptr<std::vector<unsigned char>> & data)
    {
      FileInfo fileInfo;
      if (this->offset == 0 && data) {
        this->offset = data->size();
      }
      if (!data || data->empty()) {
        fileInfo.Format = analyzer::core::FileFormat::empty;
      }
      else if (this->isXML(data)) {
        fileInfo.Format = analyzer::core::FileFormat::xml;
      }
      else if (this->isPDF(data)) {
        fileInfo.Format = analyzer::core::FileFormat::pdf;
      }
      else if (this->isWinExec(data)) {
        fileInfo.Format = analyzer::core::FileFormat::winExec;
      }
      else if (this->isBmp(data)) {
        fileInfo.Format = analyzer::core::FileFormat::bmp;
      }
      else if (this->isASCII(data)) {
        fileInfo.Format = analyzer::core::FileFormat::ascii;
      }
      else {
        fileInfo.Format = analyzer::core::FileFormat::unknown;
      }
      this->indexBegin = 0;
      this->offset = 0;
      return fileInfo;
    }

    FileInfo TypeAnalyzer::GetFileInfo(const std::shared_ptr<std::vector<unsigned char>>& data, const size_t & indexBegin, const size_t & offset)
    {
      this->indexBegin = indexBegin;
      this->offset = offset;
      return this->GetFileInfo(data);
    }

    bool TypeAnalyzer::isXML(const std::shared_ptr<std::vector<unsigned char>>& data)
    {
      if (this->offset < 25) {
        return false;
      }
      auto text(TypeAnalyzer::toASCII(data, this->indexBegin, 25));

      size_t startIndex = text.find("<?xml version=");
      if (startIndex < text.size()) {
        return true;
      }
      else {
        return false;
      }
      return true;
    }

    bool TypeAnalyzer::isASCII(const std::shared_ptr<std::vector<unsigned char>>& data)
    {
      size_t analyzeOffset = 100;
      if (this->offset < analyzeOffset - 1) {
        analyzeOffset = this->offset - 1;
      }

      bool nonASCII = false;
      for (size_t i = this->indexBegin; i < this->indexBegin + analyzeOffset; ++i) {
        int numVal = data->at(i);
        if ((numVal > 31 && numVal < 127) ||
          (numVal == 10) ||
          (numVal == 13) ||
          (numVal == 128) ||
          (numVal == 130) ||
          (numVal == 158) ||
          (numVal == 159) ||
          (numVal > 144 && numVal < 157) ||
          (numVal > 160 && numVal < 173) ||
          (numVal > 173 && numVal < 256)
          ) {
          continue;
        }
        else {
          nonASCII = true;
          break;
        }
      }

      if (nonASCII) {
        return false;
      }
      else {
        return true;
      }
      
    }

    bool TypeAnalyzer::isPDF(const std::shared_ptr<std::vector<unsigned char>>& data)
    {
      if (this->offset < 8) {
        return false;
      }
      auto text(TypeAnalyzer::toASCII(data, this->indexBegin, 8));

      size_t startIndex = text.find("%PDF-");
      if (startIndex < text.size()) {
        return true;
      }
      else {
        return false;
      }
      return true;
    }

    bool TypeAnalyzer::isWinExec(const std::shared_ptr<std::vector<unsigned char>>& data)
    {
      if (this->offset < LenDosHeaderInclMsg) {
        return false;
      }

      std::string DOSHeaderStart(toASCII(data, this->indexBegin, 2));
      if (DOSHeaderStart.compare("MZ") == 0 ||
        DOSHeaderStart.compare("ZM") == 0) {
        std::string DOSHeaderMsg(toASCII(data, 78, 39));
        if (DOSHeaderMsg.compare("This program cannot be run in DOS mode.") == 0) {
          return true;
        }
      }

      return false;
    }

    bool TypeAnalyzer::isBmp(const std::shared_ptr<std::vector<unsigned char>>& data)
    {
      if (this->offset < LenBMPHeader) {
        return false;
      }
      std::string BMPHeaderStart(toASCII(data, this->indexBegin, 2));
      if (BMPHeaderStart.compare("BM") == 0) {

        unsigned int minOffsetToDataSection = 50;
        unsigned int size = *reinterpret_cast<const uint32_t*>(&data->at(this->indexBegin + 2));
        unsigned short res1 = *reinterpret_cast<const uint16_t*>(&data->at(this->indexBegin + 6));
        unsigned short res2 = *reinterpret_cast<const uint16_t*>(&data->at(this->indexBegin + 8));
        unsigned int off = *reinterpret_cast<const uint32_t*>(&data->at(this->indexBegin + 10));
        unsigned int compression = *reinterpret_cast<const uint32_t*>(&data->at(this->indexBegin + 30));
        if(off > minOffsetToDataSection &&
          (compression >= 0 && compression <= 3)){
          return true;
        }
      }
      return false;
    }

    std::string TypeAnalyzer::toASCII(const std::shared_ptr<std::vector<unsigned char>>& data, const size_t & index, const size_t & offset)
    {
      if (index + offset > data->size()) {
        throw CoreException("Invalid index or offset value in TypeAnalyzer::toASCII()");
      }
      std::string text;
      for (size_t i = index; i < index + offset; ++i) {
        text.push_back(static_cast<char>(data->at(i)));
      }
      return text;
    }

    TypeAnalyzer * TypeAnalyzer::instance = nullptr;
      
  }
}

//MZê This program cannot be run in DOS mode.