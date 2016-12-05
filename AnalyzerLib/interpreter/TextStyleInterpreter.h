#ifndef TEXTSTYLEINTERPRETER_H
#define TEXTSTYLEINTERPRETER_H

#if _USRDLL
#define IMEX __declspec(dllexport)
#else
#define IMEX __declspec(dllimport)
#endif

#include <memory>

#include "InterpreterDataImpl.h"
#include "TextGlyph.h"

namespace analyzer{
  namespace interpreter{
    class IMEX TextStyleInterpreter : public InterpreterDataImpl
    {
    public:
      TextStyleInterpreter();
      virtual ~TextStyleInterpreter();

      virtual std::string GetPlainText();
    };
  }
}

#endif