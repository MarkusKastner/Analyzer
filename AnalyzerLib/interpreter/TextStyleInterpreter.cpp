#include "TextStyleInterpreter.h"

#include "error\InterpreterException.h"

namespace analyzer{
  namespace interpreter{
    TextStyleInterpreter::TextStyleInterpreter()
      :InterpreterDataImpl()
    {

    }

    TextStyleInterpreter::~TextStyleInterpreter()
    {

    }

    std::string TextStyleInterpreter::GetPlainText()
    {
      return "";
    }
  }
}