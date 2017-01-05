#include "FormatFinder.h"

namespace analyzer{
  namespace core{
    FormatFinder::FormatFinder()
      : data(new std::shared_ptr<analyzer::core::ByteCollection>())
    {

    }

    FormatFinder::~FormatFinder()
    {
      delete this->data;
    }

    analyzer::core::FormatFinder::Format FormatFinder::Analyze(const std::shared_ptr<analyzer::core::ByteCollection> & data)
    {
      *this->data = data;
      bool isText = false;
      if (!this->hasNoneASCIIBytes()){
        isText = true;
        return Format::ascii;
      }
      
    }

    bool FormatFinder::hasNoneASCIIBytes()
    {
      for (auto& byte : (**this->data)){
        if (byte->GetBitAt(7) == 1){
          return true;
        }
      }
      return false;
    }

  }
}