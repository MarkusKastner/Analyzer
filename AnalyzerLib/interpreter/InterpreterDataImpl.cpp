#include "InterpreterDataImpl.h"

#include "error\InterpreterException.h"

namespace analyzer{
  namespace interpreter{

    InterpreterDataImpl::InterpreterDataImpl()
      :InterpreterObserverImpl(), byteCollection(new std::shared_ptr<analyzer::core::ByteCollection>(new analyzer::core::ByteCollection())), 
      glyphs(new std::vector<std::shared_ptr<TextGlyph>>()),
      dataLock(new std::recursive_mutex()), glyphsLock(new std::recursive_mutex())
    {
    }

    InterpreterDataImpl::InterpreterDataImpl(const std::shared_ptr<analyzer::core::ByteCollection> & byteCollection)
      : InterpreterObserverImpl(), byteCollection(new std::shared_ptr<analyzer::core::ByteCollection>(byteCollection)), 
      glyphs(new std::vector<std::shared_ptr<TextGlyph>>()),
      dataLock(new std::recursive_mutex()), glyphsLock(new std::recursive_mutex())
    {
    }

    InterpreterDataImpl::~InterpreterDataImpl()
    {
      delete this->byteCollection;
      delete this->glyphs;
      delete this->dataLock;
      delete this->glyphsLock;
    }

    bool InterpreterDataImpl::HasData()
    {
      std::lock_guard<std::recursive_mutex> lock(*this->dataLock);
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
      { std::lock_guard<std::recursive_mutex> lock(*this->dataLock);
      *this->byteCollection = data;
      }
      this->onNewData();
    }

    void InterpreterDataImpl::ResetData(const std::vector<char> & data)
    {
      { std::lock_guard<std::recursive_mutex> lock(*this->dataLock);
      this->byteCollection->reset(new core::ByteCollection(data));
      }
      this->onNewData();
    }

    std::shared_ptr<analyzer::core::ByteCollection> InterpreterDataImpl::GetData()
    {
      std::lock_guard<std::recursive_mutex> lock(*this->dataLock);
      return *this->byteCollection;
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
      std::lock_guard<std::recursive_mutex> lock(*this->dataLock);
      return this->byteCollection;
    }

    void InterpreterDataImpl::clearGlyphs()
    {
      std::lock_guard<std::recursive_mutex> lock(*this->glyphsLock);
      this->glyphs->clear();
    }

    void InterpreterDataImpl::addGlyph(const std::shared_ptr<TextGlyph> & glyph)
    {
      std::lock_guard<std::recursive_mutex> lock(*this->glyphsLock);
      this->glyphs->push_back(glyph);
    }

    std::string InterpreterDataImpl::getPlainText()
    {
      std::lock_guard<std::recursive_mutex> lock(*this->glyphsLock);
      std::string text;
      for (auto glyph : *this->glyphs){
        text += glyph->GetPlainText();
      }
      return text;
    }

    void InterpreterDataImpl::createGlyphs()
    {
      std::lock_guard<std::recursive_mutex> lock(*this->dataLock);
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