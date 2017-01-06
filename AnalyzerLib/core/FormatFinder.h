#ifndef FORMATFINDER_H
#define FORMATFINDER_H

#include <memory>

#include "AnalyzerLib\core\ByteCollection.h"

namespace analyzer{
  namespace core{
    class FormatFinder
    {
    public:
      enum Format
      {
        unknown = 0,
        text,
        binary,
        xml,
        pdf
      };

      FormatFinder();
      virtual ~FormatFinder();

      void SetData(const std::shared_ptr<analyzer::core::ByteCollection> & data);
      void Analyze();
      analyzer::core::FormatFinder::Format GetBaseFormat();
      analyzer::core::FormatFinder::Format GetDetailFormat();

    private:
      std::shared_ptr<analyzer::core::ByteCollection> * data;
      analyzer::core::FormatFinder::Format baseFormat;
      analyzer::core::FormatFinder::Format detailFormat;

      void analyzeBaseFormat();
      void analyzeDetailTextFormat();
      
      bool isLetter(const std::shared_ptr<Byte> & byte);
      bool isXML();

    };
  }
}

#endif
