#include "BinaryStyleInterpreter.h"

#include "error\InterpreterException.h"

namespace analyzer{
  namespace interpreter{

    BinaryStyleInterpreter::BinaryStyleInterpreter()
      :InterpreterObserverImpl(), byteCollection(new std::shared_ptr<analyzer::core::ByteCollection>()), glyphs(new std::vector<std::shared_ptr<TextGlyph>>())
    {
    }

    BinaryStyleInterpreter::BinaryStyleInterpreter(const std::shared_ptr<analyzer::core::ByteCollection> & byteCollection)
      : InterpreterObserverImpl(), byteCollection(new std::shared_ptr<analyzer::core::ByteCollection>(byteCollection)), glyphs(new std::vector<std::shared_ptr<TextGlyph>>())
    {
      this->createGlyphs();
    }

    BinaryStyleInterpreter::~BinaryStyleInterpreter()
    {
      delete this->byteCollection;
      delete this->glyphs;
    }

    bool BinaryStyleInterpreter::HasData()
    {
      if (!(*this->byteCollection)){
        return false;
      }
      if ((*this->byteCollection)->GetSize() == 0){
        return false;
      }
      else{
        return true;
      }
    }
    
    void BinaryStyleInterpreter::ResetData(const std::shared_ptr<analyzer::core::ByteCollection> & data)
    {
      *this->byteCollection = data;
      this->createGlyphs();
    }

    std::string BinaryStyleInterpreter::GetPlainText()
    {
      std::string output;
      for (auto byte : *this->byteCollection->get()){
        output += byte->GetBitsAsString();
        output += " ";
      }
      output.pop_back();
      return output;
    }

    size_t BinaryStyleInterpreter::NumGlyphs() const
    {
      return this->glyphs->size();
    }

    std::shared_ptr<TextGlyph> BinaryStyleInterpreter::GetGlyphAt(const size_t & index)
    {
      this->throwGlyphIndex(index);
      return this->glyphs->at(index);
    }

    void BinaryStyleInterpreter::createGlyphs()
    {
      this->glyphs->clear();
      if ((*this->byteCollection)->GetSize() <= 0){
        return;
      }
      for (auto byte : *this->byteCollection->get()){
        std::vector<std::shared_ptr<analyzer::core::Byte>> bytes;
        bytes.push_back(byte);
        this->glyphs->push_back(std::shared_ptr<TextGlyph>(new TextGlyph(bytes)));
      }
    }

    void BinaryStyleInterpreter::throwGlyphIndex(const size_t & index)
    {
      if (this->glyphs->size() == 0 || index > this->glyphs->size() - 1){
        throw InterpreterException("Invalid index");
      }
    }
  }
}