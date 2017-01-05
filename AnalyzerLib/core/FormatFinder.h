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
        ascii,
        UTF8
      };

      FormatFinder();
      virtual ~FormatFinder();

      analyzer::core::FormatFinder::Format Analyze(const std::shared_ptr<analyzer::core::ByteCollection> & data);

    private:
      std::shared_ptr<analyzer::core::ByteCollection> * data;

      bool hasNoneASCIIBytes();

    };
  }
}

#endif
