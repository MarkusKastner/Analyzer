/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "Byte.h"

#include <bitset>

#include "error\CoreException.h"

namespace analyzer{
  namespace core{

    bool operator==(const Byte & b1, const Byte & b2)
    {
      return b1.GetValue() == b2.GetValue();
    }

    Byte::Byte()
      : BasicType(), value(0)
    {
    }

    Byte::Byte(const unsigned char & value)
      : BasicType(), value(value)
    {
    }

    Byte::~Byte()
    {
    }

    const unsigned char & Byte::GetValue() const
    {
      return this->value;
    }

    unsigned int Byte::GetBitAt(const unsigned int & index)
    {
      if (index > ByteSize - 1){
        throw CoreException("Bit index out of range");
      }
      return std::bitset<ByteSize>(this->value).at(index);
    }

    std::string Byte::GetBitsAsString()
    {
      return std::bitset<ByteSize>(this->value).to_string();
    }
  }
}