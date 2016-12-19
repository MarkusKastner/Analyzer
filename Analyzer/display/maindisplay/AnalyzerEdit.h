#ifndef ANALYZEREDIT_H
#define ANALYZEREDIT_H

#include <QTextEdit>
#include <QEvent>

#include "AnalyzerLib\interpreter\TextChangedObserver.h"

namespace analyzer{
  namespace interpreter{
    class Interpreter;
  }
  namespace gui{
    namespace display{
      class AnalyzerEdit : public QTextEdit, public interpreter::TextChangedObserver
      {
      private:
        class EditEvent : public QEvent
        {
        public:
          EditEvent()
            :QEvent(Type::User)
          {}
          virtual ~EditEvent(){}
        };
      public:
        AnalyzerEdit(QWidget * parent = 0);
        virtual ~AnalyzerEdit();

        virtual void NotifyDataChanged();

        void SetInterpreter(interpreter::Interpreter * interpreter);
        void ClearInterpreter();

      protected:
        void customEvent(QEvent * evt);

      private:
        interpreter::Interpreter * interpreter;
      };
    }
  }
}
#endif