#ifndef TEXTGLYPH_H
#define TEXTGLYPH_H

#if _USRDLL
#define IMEX __declspec(dllexport)
#else
#define IMEX __declspec(dllimport)
#endif

#include <memory>
#include <vector>

#include "AnalyzerLib\core\Byte.h"
#include "strategy\InterpretStrategy.h"

namespace analyzer{
  namespace interpreter{
    class IMEX TextGlyph
    {
    public:
      TextGlyph();
      explicit TextGlyph(const std::vector<std::shared_ptr<analyzer::core::Byte>> & data);
      virtual ~TextGlyph();

      bool operator==(const TextGlyph& other){
        return true;
      }

      bool HasExpression();
      size_t NumBytes();
      std::string GetPlainText();

    private:
      std::vector<std::shared_ptr<analyzer::core::Byte>> * data;
      strategy::InterpretStrategy * interpretStrategy;
    };
  }
}
#endif