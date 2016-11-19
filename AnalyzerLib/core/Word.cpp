#include "Word.h"

#include "error\CoreException.h"

namespace analyzer{
  namespace core{

    Word::Word()
      :BasicType(), lowByte(), highByte()
    {

    }

    Word::~Word()
    {

    }
  
    Word::Word(const Byte & highByte, const Byte & lowByte)
      :BasicType(), lowByte(lowByte), highByte(highByte)
    {

    }

    unsigned int Word::GetBitAt(const unsigned int & index)
    {
      if (index < 8){
        return this->lowByte.GetBitAt(index);
      }
      else if (index >= 8 && index < 16){
        return this->highByte.GetBitAt(index - 8);
      }
      else{
        throw CoreException("Bit index out of range");
      }
    }

    std::string Word::GetBitsAsString()
    {
      return this->highByte.GetBitsAsString() + std::string(" ") + this->lowByte.GetBitsAsString();
    }

    unsigned short Word::GetValue() const
    {
      unsigned short word = (this->highByte.GetValue() << 8) | this->lowByte.GetValue();
      return word;
    }
  }
}