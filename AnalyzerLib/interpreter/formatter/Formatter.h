#ifndef FORMATTER_H
#define FORMATTER_H

#if _USRDLL
#define IMEX __declspec(dllexport)
#else
#define IMEX __declspec(dllimport)
#endif

#include "AnalyzerLib\core\ByteCollection.h"

namespace analyzer{
  namespace interpreter{
    class IMEX Formatter
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