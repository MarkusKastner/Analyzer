#ifndef INTERPRETSTRATEGY_H
#define INTERPRETSTRATEGY_H

#if _USRDLL
#define IMEX __declspec(dllexport)
#else
#define IMEX __declspec(dllimport)
#endif

#include <string>

namespace analyzer{
  namespace interpreter{
    namespace strategy{
      class IMEX InterpretStrategy
      {
      public:
        virtual std::string GetPlainText() = 0;
      };
    }
  }
}

#endif