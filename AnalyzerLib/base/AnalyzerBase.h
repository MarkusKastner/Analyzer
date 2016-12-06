#ifndef ANALYZERBASE_H
#define ANALYZERBASE_H

#if _USRDLL
#define IMEX __declspec(dllexport)
#else
#define IMEX __declspec(dllimport)
#endif

#include <memory>

namespace analyzer{
  namespace interpreter{
    class Interpreter;
  }
  namespace base{
    class IMEX AnalyzerBase
    {
    public:
      AnalyzerBase();
      virtual ~AnalyzerBase();

      bool HasInterpreter();
      interpreter::Interpreter * Interpreter();

      void SetBinaryMode();
      void SetTextMode();

    private:
      std::unique_ptr<interpreter::Interpreter> * interpreter;
    };
  }
}
#endif