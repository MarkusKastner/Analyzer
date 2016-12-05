#ifndef INTERPRETEROBSERVERIMPL_H
#define INTERPRETEROBSERVERIMPL_H

#include <memory>
#include <string>

#include "Interpreter.h"
#include "TextChangedObserver.h"

namespace analyzer{
  namespace interpreter{
    class TextChangedObserver;
    class InterpreterObserverImpl : public Interpreter
    {
    public:
      virtual ~InterpreterObserverImpl();

      virtual bool HasObservers();
      virtual size_t NumberOfObservers();
      virtual void RegisterObserver(TextChangedObserver * observer);
      virtual void UnregisterObserver(TextChangedObserver * observer);
      virtual void NotifyTextChange();

    protected:
      InterpreterObserverImpl();

    private:
      std::vector<TextChangedObserver*> textChangeObservers;

      void throwInvalidObserver(TextChangedObserver * observer);
    };
  }
}
#endif