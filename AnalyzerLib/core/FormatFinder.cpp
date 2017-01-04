#include "FormatFinder.h"

namespace analyzer{
  namespace core{
    FormatFinder::FormatFinder()
    {

    }

    FormatFinder::~FormatFinder()
    {

    }

    analyzer::core::FormatFinder::Format FormatFinder::Analyze(const std::shared_ptr<analyzer::core::ByteCollection> & data)
    {
      return Format::ascii;
    }

  }
}