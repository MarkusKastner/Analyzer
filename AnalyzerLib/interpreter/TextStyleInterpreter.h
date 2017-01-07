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
      explicit TextStyleInterpreter(const std::shared_ptr<analyzer::core::ByteCollection> & byteCollection);
      virtual ~TextStyleInterpreter();

      virtual std::string GetPlainText();
      virtual std::wstring GetFormatedText();

    protected:
      virtual void createGlyphs();
    };
  }
}

#endif