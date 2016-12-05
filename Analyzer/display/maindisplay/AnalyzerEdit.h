#ifndef ANALYZEREDIT_H
#define ANALYZEREDIT_H

#include <QTextEdit>
#include "AnalyzerLib\interpreter\TextChangedObserver.h"

namespace analyzer{
  namespace interpreter{
    class Interpreter;
  }
  namespace gui{
    namespace display{
      class AnalyzerEdit : public QTextEdit, public interpreter::TextChangedObserver
      {
      public:
        AnalyzerEdit(QWidget * parent = 0);
        virtual ~AnalyzerEdit();

        virtual void NotifyDataChanged();

        void SetInterpreter(interpreter::Interpreter * interpreter);

      private:
        interpreter::Interpreter * interpreter;
      };
    }
  }
}
#endif