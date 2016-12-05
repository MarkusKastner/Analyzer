#ifndef BASICTYPE_H
#define BASICTYPE_H

#if _USRDLL
#define IMEX __declspec(dllexport)
#else
#define IMEX __declspec(dllimport)
#endif

#include <string>

namespace analyzer{
  namespace core{
    class IMEX BasicType
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