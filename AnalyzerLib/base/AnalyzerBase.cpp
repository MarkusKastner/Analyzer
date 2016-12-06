#include "AnalyzerBase.h"

#include "AnalyzerLib\interpreter\Interpreter.h"
#include "AnalyzerLib\interpreter\BinaryStyleInterpreter.h"
#include "AnalyzerLib\interpreter\TextStyleInterpreter.h"

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

    void AnalyzerBase::SetBinaryMode()
    {
      if (!dynamic_cast<interpreter::BinaryStyleInterpreter*>(this->interpreter->get())){
        this->interpreter->reset(new interpreter::BinaryStyleInterpreter());
      }
    }

    void AnalyzerBase::SetTextMode()
    {
      if (!dynamic_cast<interpreter::TextStyleInterpreter*>(this->interpreter->get())){
        this->interpreter->reset(new interpreter::TextStyleInterpreter());
      }
    }
  }
}