#ifndef INTERPRETERDATAIMPL_H
#define INTERPRETERDATAIMPL_H

#if _USRDLL
#define IMEX __declspec(dllexport)
#else
#define IMEX __declspec(dllimport)
#endif

#include <memory>

#include "InterpreterObserverImpl.h"
#include "TextGlyph.h"

namespace analyzer{
  namespace interpreter{
    class IMEX InterpreterDataImpl : public InterpreterObserverImpl
    {
    public:
      InterpreterDataImpl();
      explicit InterpreterDataImpl(const std::shared_ptr<analyzer::core::ByteCollection> & byteCollection);
      virtual ~InterpreterDataImpl();

      virtual bool HasData();
      virtual void ResetData(const std::shared_ptr<analyzer::core::ByteCollection> & data);
      virtual void ResetData(const std::vector<char> & data);

      virtual size_t NumGlyphs() const;
      virtual std::shared_ptr<TextGlyph> GetGlyphAt(const size_t & index);

    protected:
      std::shared_ptr<analyzer::core::ByteCollection> * getByteCollection();
      void clearGlyphs();
      void addGlyph(const std::shared_ptr<TextGlyph> & glyph);
      std::string getPlainText();

      virtual void createGlyphs();

    private:
      std::shared_ptr<analyzer::core::ByteCollection> * byteCollection;
      std::vector<std::shared_ptr<TextGlyph>> * glyphs;

      void onNewData();
      

      void throwGlyphIndex(const size_t & index);
    };
  }
}
#endif