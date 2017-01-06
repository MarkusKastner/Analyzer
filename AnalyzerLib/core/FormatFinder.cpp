#include "FormatFinder.h"

namespace analyzer{
  namespace core{
    FormatFinder::FormatFinder()
      : data(new std::shared_ptr<analyzer::core::ByteCollection>()),
      baseFormat(Format::unknown), detailFormat(Format::unknown)
    {
    }

    FormatFinder::~FormatFinder()
    {
      delete this->data;
    }

    void FormatFinder::SetData(const std::shared_ptr<analyzer::core::ByteCollection> & data)
    {
      *this->data = data;
    }

    void FormatFinder::Analyze()
    {
      this->analyzeBaseFormat();
    }

    analyzer::core::FormatFinder::Format FormatFinder::GetBaseFormat()
    {
      return this->baseFormat;
    }

    analyzer::core::FormatFinder::Format FormatFinder::GetDetailFormat()
    {
      return this->detailFormat;
    }

    void FormatFinder::analyzeBaseFormat()
    {
      size_t totalTested = 0;
      size_t letters = 0;
      for (auto& byte : (**this->data)){
        totalTested++;
        if (this->isLetter(byte)){
          letters++;
        }
      }

      if (letters > (totalTested / 2)){
        this->baseFormat = Format::text;
        this->analyzeDetailTextFormat();
      }
      else{
        this->baseFormat = Format::binary;
      }
    }

    void FormatFinder::analyzeDetailTextFormat()
    {
      if (this->isXML()){
        this->detailFormat = Format::xml;
        return;
      }
      this->detailFormat = Format::unknown;
    }

    bool FormatFinder::isLetter(const std::shared_ptr<Byte> & byte)
    {
      unsigned int valAsInt = byte->GetValue();
      if (valAsInt > 31 && valAsInt < 127){
        return true;
      }
      else if (valAsInt > 159 && valAsInt < 191){
        return true;
      }
      else{
        return false;
      }
    }

    bool FormatFinder::isXML()
    {
      std::string text;
      for (auto& byte : (**this->data)){
        if (this->isLetter(byte)){
          text.push_back(static_cast<char>(byte->GetValue()));
        }
        if (text.size() >= 5){
          if (text.substr(0, 5).compare("<?xml") == 0){
            return true;
          }
          else{
            return false;
          }
        }
      }
      return false;
    }
  }
}