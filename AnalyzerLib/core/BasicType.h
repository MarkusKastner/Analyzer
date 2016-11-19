#ifndef BASICTYPE_H
#define BASICTYPE_H

#include <string>

namespace analyzer{
  namespace core{
    class BasicType
    {
    public:
      virtual ~BasicType();

      virtual unsigned int GetBitAt(const unsigned int & index) = 0;
      virtual std::string GetBitsAsString() = 0;

    protected:
      BasicType();

    };
  }
}
#endif