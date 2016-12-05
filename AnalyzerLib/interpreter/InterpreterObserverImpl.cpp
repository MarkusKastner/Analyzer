#include "InterpreterObserverImpl.h"

#include "error\InterpreterException.h"

namespace analyzer{
  namespace interpreter{

    InterpreterObserverImpl::InterpreterObserverImpl()
      : textChangeObservers(new std::vector<TextChangedObserver*>())
    {
    }

    InterpreterObserverImpl::~InterpreterObserverImpl()
    {
      delete this->textChangeObservers;
    }

    bool InterpreterObserverImpl::HasObservers()
    {
      return !this->textChangeObservers->empty();
    }

    size_t InterpreterObserverImpl::NumberOfObservers()
    {
      return this->textChangeObservers->size();
    }

    void InterpreterObserverImpl::RegisterObserver(TextChangedObserver * observer)
    {
      this->throwInvalidObserver(observer);
      for (auto it = this->textChangeObservers->begin(); it != textChangeObservers->end(); ++it){
        if (*it == observer){
          return;
        }
      }
      this->textChangeObservers->push_back(observer);
    }

    void InterpreterObserverImpl::UnregisterObserver(TextChangedObserver * observer)
    {
      this->throwInvalidObserver(observer);
      for (auto it = this->textChangeObservers->begin(); it != textChangeObservers->end(); ++it){
        if (*it == observer){
          this->textChangeObservers->erase(it);
          return;
        }
      }
    }

    void InterpreterObserverImpl::NotifyTextChange()
    {
      for (auto observer : *this->textChangeObservers){
        observer->NotifyDataChanged();
      }
    }

    void InterpreterObserverImpl::throwInvalidObserver(TextChangedObserver * observer)
    {
      if (nullptr == observer){
        throw InterpreterException("Invalid observer");
      }
    }
  }
}