#ifndef ANALYZERBASE_H
#define ANALYZERBASE_H

#if _USRDLL
#define IMEX __declspec(dllexport)
#else
#define IMEX __declspec(dllimport)
#endif

#include <memory>
#include <vector>

namespace analyzer{
  namespace interpreter{
    class Interpreter;
  }
  namespace base{
    class AnalyzerBaseObserver;
    class IMEX AnalyzerBase
    {
    public:
      AnalyzerBase();
      virtual ~AnalyzerBase();

      bool HasInterpreter();
      interpreter::Interpreter * Interpreter();

      void SetBinaryMode();
      void SetTextMode();

      size_t NumberOfObservers();
      void RegisterObserver(AnalyzerBaseObserver * observer);
      void UnregisterObserver(AnalyzerBaseObserver * observer);

    private:
      std::unique_ptr<interpreter::Interpreter> * interpreter;
      std::vector<AnalyzerBaseObserver*> * baseObservers;

      void notifyInterpreterChange();

      void throwInvalidObserver(AnalyzerBaseObserver * observer);
    };
  }
}
#endif