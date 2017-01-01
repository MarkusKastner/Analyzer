#ifndef DEFINITION_H
#define DEFINITION_H

#if _USRDLL
#define IMEX __declspec(dllexport)
#else
#define IMEX __declspec(dllimport)
#endif

#include <string>

namespace analyzer{
  namespace definition{
    class IMEX Definition
    {
    public:
      Definition();
      virtual ~Definition();
    };
  }
}

#endif