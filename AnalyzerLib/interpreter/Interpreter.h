#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <memory>
#include <string>

#include "AnalyzerLib\core\ByteCollection.h"
#include "AnalyzerLib\base\BaseData.h"

namespace analyzer{
  namespace interpreter{
    class TextChangedObserver;
    class TextGlyph;
    class Interpreter
    {
    public:
      virtual bool HasData() = 0;
      virtual void ResetData(const std::shared_ptr<analyzer::core::ByteCollection> & data) = 0;
      virtual void ResetData(const std::vector<char> & data) = 0;
      virtual std::shared_ptr<analyzer::core::ByteCollection> GetData() = 0;

      virtual std::string GetPlainText() = 0;
      virtual std::wstring GetFormatedText() = 0;

      virtual size_t NumGlyphs() const = 0;
      virtual std::shared_ptr<TextGlyph> GetGlyphAt(const size_t & index) = 0;

      virtual bool HasObservers() = 0;
      virtual size_t NumberOfObservers() = 0;
      virtual void RegisterObserver(TextChangedObserver * observer) = 0;
      virtual void UnregisterObserver(TextChangedObserver * observer) = 0;
      virtual void NotifyTextChange() = 0;

      virtual void SetDetailFormat(const base::DetailFormat & detailFormat, bool forceNotify = false) = 0;
    };
  }
}
#endif