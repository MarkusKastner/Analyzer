#ifndef BYTE_H
#define BYTE_H

#include <string>

namespace analyzer{
  namespace core{
    class Byte
    {
    public:
      static const unsigned int ByteSize = 8;

      Byte();
      explicit Byte(const char & value);
      virtual ~Byte();

      const char & GetValue() const;
      unsigned int GetBitAt(const unsigned int & index);
      std::string GetBitsAsString();

    private:
      char value;
     
    };
  }
}
#endif