#include "Byte.h"

#include <bitset>

namespace analyzer{
  namespace core{
    Byte::Byte()
      : value(0)
    {
    }

    Byte::Byte(const char & value)
      : value(value)
    {
    }

    Byte::~Byte()
    {
    }

    const char & Byte::GetValue() const
    {
      return this->value;
    }

    unsigned int Byte::GetBitAt(const unsigned int & index)
    {
      return std::bitset<ByteSize>(this->value).at(index);
    }

    std::string Byte::GetBitsAsString()
    {
      return std::bitset<ByteSize>(this->value).to_string();
    }
  }
}