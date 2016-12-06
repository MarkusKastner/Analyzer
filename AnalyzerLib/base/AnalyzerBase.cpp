#include "AnalyzerBase.h"

#include "AnalyzerLib\interpreter\Interpreter.h"
#include "AnalyzerLib\interpreter\BinaryStyleInterpreter.h"
#include "AnalyzerLib\interpreter\TextStyleInterpreter.h"
#include "AnalyzerLib\base\error\AnalyzerBaseException.h"
#include "AnalyzerBaseObserver.h"

namespace analyzer{
  namespace base{
    AnalyzerBase::AnalyzerBase()
      : interpreter(new std::unique_ptr<interpreter::Interpreter>()), baseObservers(new std::vector<AnalyzerBaseObserver*>())
    {
      this->interpreter->reset(new interpreter::BinaryStyleInterpreter());
    }

    AnalyzerBase::~AnalyzerBase()
    {
      delete this->interpreter;
      delete this->baseObservers;
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
        this->notifyInterpreterChange();
      }
    }

    void AnalyzerBase::SetTextMode()
    {
      if (!dynamic_cast<interpreter::TextStyleInterpreter*>(this->interpreter->get())){
        this->interpreter->reset(new interpreter::TextStyleInterpreter());
        this->notifyInterpreterChange();
      }
    }

    size_t AnalyzerBase::NumberOfObservers()
    {
      return this->baseObservers->size();
    }

    void AnalyzerBase::RegisterObserver(AnalyzerBaseObserver * observer)
    {
      this->throwInvalidObserver(observer);
      for (auto it = this->baseObservers->begin(); it != this->baseObservers->end(); ++it){
        if ((*it) == observer){
          return;
        }
      }
      this->baseObservers->push_back(observer);
    }

    void AnalyzerBase::UnregisterObserver(AnalyzerBaseObserver * observer)
    {
      this->throwInvalidObserver(observer);
      for (auto it = this->baseObservers->begin(); it != this->baseObservers->end(); ++it){
        if ((*it) == observer){
          this->baseObservers->erase(it);
          return;
        }
      }
    }

    void AnalyzerBase::notifyInterpreterChange()
    {
      for (auto observer : *this->baseObservers){
        observer->NotifyInterprterChange();
      }
    }

    void AnalyzerBase::throwInvalidObserver(AnalyzerBaseObserver * observer)
    {
      if (nullptr == observer){
        throw AnalyzerBaseException("Invalid base observer");
      }
    }
  }
}