#include "TextStyleInterpreter.h"

#include "error\InterpreterException.h"

#include "AnalyzerLib\interpreter\formatter\SimpleTextFormatter.h"
#include "AnalyzerLib\interpreter\formatter\XMLFormatter.h"

namespace analyzer{
  namespace interpreter{
    TextStyleInterpreter::TextStyleInterpreter()
      :InterpreterDataImpl()
    {

    }

    TextStyleInterpreter::TextStyleInterpreter(const std::shared_ptr<analyzer::core::ByteCollection> & byteCollection)
      :InterpreterDataImpl(byteCollection)
    {
    }

    TextStyleInterpreter::~TextStyleInterpreter()
    {
    }

    std::string TextStyleInterpreter::GetPlainText()
    {
      std::string text;
      auto& data = (**this->getByteCollection());
      for (auto& byte : data){
        text.push_back(static_cast<char>(byte->GetValue()));
      }
      return text;
    }

    std::wstring TextStyleInterpreter::GetFormatedText()
    {
      auto text(this->GetPlainText());
      return std::wstring(text.begin(), text.end());
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