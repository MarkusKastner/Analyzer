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
      
      if (!data) {
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
      return fileInfo;
    }

    bool TypeAnalyzer::isXML(const std::shared_ptr<std::vector<unsigned char>>& data)
    {
      if (data->size() < 25) {
        return false;
      }
      auto text(TypeAnalyzer::toASCII(data, 0, 25));

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
      size_t offset = 100;
      if (data->size() < offset - 1) {
        offset = data->size() - 1;
      }

      bool nonASCII = false;
      for (size_t i = 0; i < offset; ++i) {
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
      if (data->size() < 8) {
        return false;
      }
      auto text(TypeAnalyzer::toASCII(data, 0, 8));

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
      if (data->size() < LenDosHeaderInclMsg) {
        return false;
      }

      std::string DOSHeaderStart(toASCII(data, 0, 2));
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
      if (data->size() < LenBMPHeader) {
        return false;
      }
      std::string BMPHeaderStart(toASCII(data, 0, 2));
      if (BMPHeaderStart.compare("BM") == 0) {

        unsigned int minOffsetToDataSection = 50;
        unsigned int size = *reinterpret_cast<const uint32_t*>(&data->at(2));
        unsigned short res1 = *reinterpret_cast<const uint16_t*>(&data->at(6));
        unsigned short res2 = *reinterpret_cast<const uint16_t*>(&data->at(8));
        unsigned int off = *reinterpret_cast<const uint32_t*>(&data->at(10));

        if(size == data->size() &&
          res1 == 0 &&
          res2 == 0 &&
          off > minOffsetToDataSection){
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