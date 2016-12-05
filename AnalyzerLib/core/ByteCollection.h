#ifndef BYTECOLLECTION_H
#define BYTECOLLECTION_H

#include <vector>
#include <memory>

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
      const std::shared_ptr<Byte> & GetByteAt(const size_t & index);

      std::vector<std::shared_ptr<Byte>>::iterator begin();
      std::vector<std::shared_ptr<Byte>>::iterator end();
    private:
      std::vector<std::shared_ptr<Byte>> data;
    };
  }
}

#endif