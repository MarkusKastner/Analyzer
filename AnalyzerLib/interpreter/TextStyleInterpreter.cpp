#include "TextStyleInterpreter.h"

#include "error\InterpreterException.h"

namespace analyzer{
  namespace interpreter{
    TextStyleInterpreter::TextStyleInterpreter()
      :InterpreterDataImpl()
    {

    }

    TextStyleInterpreter::TextStyleInterpreter(const std::shared_ptr<analyzer::core::ByteCollection> & byteCollection)
      :InterpreterDataImpl(byteCollection)
    {
      this->createGlyphs();
    }

    TextStyleInterpreter::~TextStyleInterpreter()
    {

    }

    std::string TextStyleInterpreter::GetPlainText()
    {
      return this->getPlainText();
    }

    std::wstring TextStyleInterpreter::GetFormatedText()
    {
      return std::wstring();
    }

    bool TextStyleInterpreter::HasKnownFormat()
    {
      return false;
    }

    void TextStyleInterpreter::createGlyphs()
    {
      this->clearGlyphs();
      if ((*this->getByteCollection())->GetSize() <= 0){
        return;
      }
      std::vector<std::shared_ptr<analyzer::core::Byte>> bytes;
      for (auto byte : *this->getByteCollection()->get()){
        bytes.push_back(byte);
      }
      std::shared_ptr<TextGlyph> glyph(new TextGlyph(bytes));
      this->addGlyph(glyph);
    }
  }
}