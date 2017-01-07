#include "TextStyleInterpreter.h"

#include "error\InterpreterException.h"

#include "AnalyzerLib\interpreter\formatter\SimpleTextFormatter.h"
#include "AnalyzerLib\interpreter\formatter\XMLFormatter.h"

namespace analyzer{
  namespace interpreter{
    TextStyleInterpreter::TextStyleInterpreter()
      :InterpreterDataImpl()
    {
      this->setDetailFormatter(new SimpleTextFormatter());
    }

    TextStyleInterpreter::TextStyleInterpreter(const std::shared_ptr<analyzer::core::ByteCollection> & byteCollection)
      :InterpreterDataImpl(byteCollection)
    {
      this->setDetailFormatter(new SimpleTextFormatter());
    }

    TextStyleInterpreter::~TextStyleInterpreter()
    {
    }

    void TextStyleInterpreter::setFormatter()
    {
      switch (this->getDetailFormat()){
      case analyzer::base::DetailFormat::simpleText:
        this->setDetailFormatter(new SimpleTextFormatter());
        break;
      case analyzer::base::DetailFormat::xml:
        this->setDetailFormatter(new XMLFormatter());
        break;
      case analyzer::base::DetailFormat::pdf:
        this->setDetailFormatter(new SimpleTextFormatter());
        break;
      default:
        this->setDetailFormatter(new SimpleTextFormatter());
      }
    }
  }
}