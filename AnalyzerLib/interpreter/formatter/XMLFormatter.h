#ifndef XMLFORMATTER_H
#define XMLFORMATTER_H

#include "Formatter.h"

namespace analyzer{
  namespace interpreter{
    class XMLFormatter : public Formatter
    {
    public:
      XMLFormatter();
      virtual ~XMLFormatter();

      virtual std::wstring GetText();

    private:
      std::wstring getDataAsWString();

    };
  }
}

#endif