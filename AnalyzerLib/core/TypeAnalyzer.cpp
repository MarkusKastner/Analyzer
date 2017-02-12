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
        fileInfo.majorType = analyzer::core::MajorType::empty;
        return fileInfo;
      }

      if (this->isXML(data)) {
        fileInfo.majorType = analyzer::core::MajorType::text;
        fileInfo.minorType = analyzer::core::MinorType::xml;
        return fileInfo;
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