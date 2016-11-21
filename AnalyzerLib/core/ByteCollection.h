#ifndef BYTECOLLECTION_H
#define BYTECOLLECTION_H

#include <vector>

#include "Byte.h"

namespace analyzer{
  namespace core{
    class ByteCollection
    {
    public:
      ByteCollection();
      explicit ByteCollection(const char const *  data, const size_t & size);
      virtual ~ByteCollection();

      size_t GetSize() const;
      const Byte & GetByteAt(const size_t & index);

      std::vector<Byte>::iterator begin();
      std::vector<Byte>::iterator end();
    private:
      std::vector<Byte> data;
    };
  }
}

#endif