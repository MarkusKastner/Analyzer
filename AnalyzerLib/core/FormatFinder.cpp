#include "FormatFinder.h"

namespace analyzer{
  namespace core{
    FormatFinder::FormatFinder()
      : data(new std::shared_ptr<analyzer::core::ByteCollection>()),
      baseFormat(BaseFormat::unknown)
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

    analyzer::core::FormatFinder::BaseFormat FormatFinder::GetBaseFormat()
    {
      return this->baseFormat;
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
        this->baseFormat = BaseFormat::text;
      }
      else{
        this->baseFormat = BaseFormat::binary;
      }
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

    //analyzer::core::FormatFinder::Format FormatFinder::Analyze(const std::shared_ptr<analyzer::core::ByteCollection> & data)
    //{
    //  *this->data = data;
    //  if (!this->hasNoneASCIIBytes()){

    //    return Format::ascii;
    //  }
    //  
    //}

    //bool FormatFinder::hasNoneASCIIBytes()
    //{
    //  for (auto& byte : (**this->data)){
    //    if (byte->GetBitAt(7) == 1){
    //      return true;
    //    }
    //  }
    //  return false;
    //}

  }
}