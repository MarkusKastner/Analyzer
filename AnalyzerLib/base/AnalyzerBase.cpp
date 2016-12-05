#include "AnalyzerBase.h"

#include "AnalyzerLib\interpreter\Interpreter.h"
#include "AnalyzerLib\interpreter\BinaryStyleInterpreter.h"

namespace analyzer{
  namespace base{
    AnalyzerBase::AnalyzerBase()
      : interpreter(new std::unique_ptr<interpreter::Interpreter>())
    {
      this->interpreter->reset(new interpreter::BinaryStyleInterpreter());
    }

    AnalyzerBase::~AnalyzerBase()
    {
      delete this->interpreter;
    }

    bool AnalyzerBase::HasInterpreter()
    {
      return !(!interpreter);
    }

    interpreter::Interpreter * AnalyzerBase::Interpreter()
    {
      return this->interpreter->get();
    }
  }
}