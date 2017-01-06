#ifndef FORMATTER_H
#define FORMATTER_H

#include "AnalyzerLib\core\ByteCollection.h"

namespace analyzer{
  namespace interpreter{
    class Formatter
    {
    public:
      virtual ~Formatter();

      void SetData(const std::shared_ptr<analyzer::core::ByteCollection> & data);
      virtual std::wstring GetText() = 0;

    protected:
      Formatter();
      const std::shared_ptr<analyzer::core::ByteCollection> & getData();

    private:
      std::shared_ptr<analyzer::core::ByteCollection> * data;

    };
  }
}

#endif