#ifndef SIMPLETEXTFORMATTER_H
#define SIMPLETEXTFORMATTER_H

#include "Formatter.h"

namespace analyzer{
  namespace interpreter{
    class SimpleTextFormatter : public Formatter
    {
    public:
      SimpleTextFormatter();
      virtual ~SimpleTextFormatter();

      virtual std::wstring GetText();

    };
  }
}

#endif