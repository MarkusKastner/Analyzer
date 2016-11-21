#ifndef BYTE_H
#define BYTE_H

#include "BasicType.h"

#include <string>

namespace analyzer{
  namespace core{
    class Byte : public BasicType
    {
    public:
      static const unsigned int ByteSize = 8;

      Byte();
      explicit Byte(const unsigned char & value);
      virtual ~Byte();

      const unsigned char & GetValue() const;

      virtual unsigned int GetBitAt(const unsigned int & index);
      virtual std::string GetBitsAsString();

    private:
      unsigned char value;
     
    };

    bool operator==(const Byte & b1, const Byte & b2);
  }
}
#endif