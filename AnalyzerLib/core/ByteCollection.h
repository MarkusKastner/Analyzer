#ifndef BYTECOLLECTION_H
#define BYTECOLLECTION_H

#if _USRDLL
#define IMEX __declspec(dllexport)
#else
#define IMEX __declspec(dllimport)
#endif

#include <vector>
#include <memory>

#include "Byte.h"

namespace analyzer{
  namespace core{
    class IMEX ByteCollection
    {
    public:
      ByteCollection();
      explicit ByteCollection(const char *  data, const size_t & size);
      virtual ~ByteCollection();

      size_t GetSize() const;
      const std::shared_ptr<Byte> & GetByteAt(const size_t & index);

      std::vector<std::shared_ptr<Byte>>::iterator begin();
      std::vector<std::shared_ptr<Byte>>::iterator end();
    private:
      std::vector<std::shared_ptr<Byte>> * data;
    };
  }
}

#endif