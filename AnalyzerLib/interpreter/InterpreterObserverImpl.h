/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef INTERPRETEROBSERVERIMPL_H
#define INTERPRETEROBSERVERIMPL_H

#if _USRDLL
#define IMEX __declspec(dllexport)
#else
#define IMEX __declspec(dllimport)
#endif

#include <memory>
#include <string>

#include "Interpreter.h"
#include "TextChangedObserver.h"

namespace analyzer{
  namespace interpreter{
    class IMEX InterpreterObserverImpl : public Interpreter
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
      std::vector<TextChangedObserver*> * textChangeObservers;

      void notifyExInterpreter();
      void throwInvalidObserver(TextChangedObserver * observer);
    };
  }
}
#endif