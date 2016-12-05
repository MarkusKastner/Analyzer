#include "BinaryStyleInterpreter.h"

#include "error\InterpreterException.h"

namespace analyzer{
  namespace interpreter{

    BinaryStyleInterpreter::BinaryStyleInterpreter()
      : byteCollection(), gylphs(), textChangeObservers()
    {
    }

    BinaryStyleInterpreter::BinaryStyleInterpreter(const std::shared_ptr<analyzer::core::ByteCollection> & byteCollection)
      : byteCollection(byteCollection), gylphs()
    {
      this->createGlyphs();
    }

    BinaryStyleInterpreter::~BinaryStyleInterpreter()
    {

    }

    bool BinaryStyleInterpreter::HasData()
    {
      if (!this->byteCollection){
        return false;
      }
      if (this->byteCollection->GetSize() == 0){
        return false;
      }
      else{
        return true;
      }
    }
    
    void BinaryStyleInterpreter::ResetData(const std::shared_ptr<analyzer::core::ByteCollection> & data)
    {
      this->byteCollection = data;
      this->createGlyphs();
    }

    std::string BinaryStyleInterpreter::GetPlainText()
    {
      std::string output;
      for (auto byte : *this->byteCollection.get()){
        output += byte->GetBitsAsString();
        output += " ";
      }
      output.pop_back();
      return output;
    }

    bool BinaryStyleInterpreter::HasObservers()
    {
      return !this->textChangeObservers.empty();
    }

    void BinaryStyleInterpreter::RegisterObserver(TextChangedObserver * observer)
    {
      this->textChangeObservers.push_back(observer);
    }

    size_t BinaryStyleInterpreter::NumGlyphs() const
    {
      return this->gylphs.size();
    }

    std::shared_ptr<TextGlyph> BinaryStyleInterpreter::GetGlyphAt(const size_t & index)
    {
      this->throwGlyphIndex(index);
      return this->gylphs.at(index);
    }

    void BinaryStyleInterpreter::createGlyphs()
    {
      this->gylphs.clear();
      if (this->byteCollection->GetSize() <= 0){
        return;
      }
      for (auto byte : *this->byteCollection.get()){
        std::vector<std::shared_ptr<analyzer::core::Byte>> bytes;
        bytes.push_back(byte);
        this->gylphs.push_back(std::shared_ptr<TextGlyph>(new TextGlyph(bytes)));
      }
    }

    void BinaryStyleInterpreter::throwGlyphIndex(const size_t & index)
    {
      if (this->gylphs.size() == 0 || index > this->gylphs.size() - 1){
        throw InterpreterException("Invalid index");
      }
    }
  }
}