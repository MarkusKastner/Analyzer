#include "InterpreterDataImpl.h"

#include "error\InterpreterException.h"

namespace analyzer{
  namespace interpreter{

    InterpreterDataImpl::InterpreterDataImpl()
      :InterpreterObserverImpl(), byteCollection(new std::shared_ptr<analyzer::core::ByteCollection>()), glyphs(new std::vector<std::shared_ptr<TextGlyph>>())
    {
    }

    InterpreterDataImpl::InterpreterDataImpl(const std::shared_ptr<analyzer::core::ByteCollection> & byteCollection)
      : InterpreterObserverImpl(), byteCollection(new std::shared_ptr<analyzer::core::ByteCollection>(byteCollection)), glyphs(new std::vector<std::shared_ptr<TextGlyph>>())
    {
    }

    InterpreterDataImpl::~InterpreterDataImpl()
    {
      delete this->byteCollection;
      delete this->glyphs;
    }

    bool InterpreterDataImpl::HasData()
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

    void InterpreterDataImpl::ResetData(const std::shared_ptr<analyzer::core::ByteCollection> & data)
    {
      *this->byteCollection = data;
      this->onNewData();
    }

    void InterpreterDataImpl::ResetData(const std::vector<char> & data)
    {
      this->byteCollection->reset(new core::ByteCollection(data));
      this->onNewData();
    }

    size_t InterpreterDataImpl::NumGlyphs() const
    {
      return this->glyphs->size();
    }

    std::shared_ptr<TextGlyph> InterpreterDataImpl::GetGlyphAt(const size_t & index)
    {
      this->throwGlyphIndex(index);
      return this->glyphs->at(index);
    }

    std::shared_ptr<analyzer::core::ByteCollection> * InterpreterDataImpl::getByteCollection()
    {
      return this->byteCollection;
    }

    void InterpreterDataImpl::clearGlyphs()
    {
      this->glyphs->clear();
    }

    void InterpreterDataImpl::addGlyph(const std::shared_ptr<TextGlyph> & glyph)
    {
      this->glyphs->push_back(glyph);
    }

    std::string InterpreterDataImpl::getPlainText()
    {
      std::string text;
      for (auto glyph : *this->glyphs){
        text += glyph->GetPlainText();
      }
      return text;
    }

    void InterpreterDataImpl::createGlyphs()
    {
      this->clearGlyphs();
      if ((*this->byteCollection)->GetSize() <= 0){
        return;
      }
      for (auto byte : *this->byteCollection->get()){
        std::vector<std::shared_ptr<analyzer::core::Byte>> bytes;
        bytes.push_back(byte);
        this->addGlyph(std::shared_ptr<TextGlyph>(new TextGlyph(bytes)));
      }
    }

    void InterpreterDataImpl::onNewData()
    {
      this->createGlyphs();
      this->NotifyTextChange();
    }

    void InterpreterDataImpl::throwGlyphIndex(const size_t & index)
    {
      if (this->glyphs->size() == 0 || index > this->glyphs->size() - 1){
        throw InterpreterException("Invalid index");
      }
    }
  }
}