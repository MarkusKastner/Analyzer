#ifndef FORMATFINDER_H
#define FORMATFINDER_H

#include <memory>

#include "AnalyzerLib\core\ByteCollection.h"

namespace analyzer{
  namespace core{
    class FormatFinder
    {
    public:
      enum BaseFormat
      {
        unknown = 0,
        text,
        binary
      };

      FormatFinder();
      virtual ~FormatFinder();

      void SetData(const std::shared_ptr<analyzer::core::ByteCollection> & data);
      void Analyze();
      analyzer::core::FormatFinder::BaseFormat GetBaseFormat();

    private:
      std::shared_ptr<analyzer::core::ByteCollection> * data;
      analyzer::core::FormatFinder::BaseFormat baseFormat;

      void analyzeBaseFormat();
      bool isLetter(const std::shared_ptr<Byte> & byte);

    };
  }
}

#endif
