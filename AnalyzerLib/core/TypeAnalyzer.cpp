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