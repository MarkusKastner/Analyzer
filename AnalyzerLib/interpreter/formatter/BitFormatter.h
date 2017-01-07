#ifndef BITFORMATTER_H
#define BITFORMATTER_H

#if _USRDLL
#define IMEX __declspec(dllexport)
#else
#define IMEX __declspec(dllimport)
#endif

#include "Formatter.h"

namespace analyzer{
  namespace interpreter{
    class IMEX BitFormatter : public Formatter
    {
    public:
      BitFormatter();
      virtual ~BitFormatter();

      virtual std::wstring GetText();

    };
  }
}
#endif