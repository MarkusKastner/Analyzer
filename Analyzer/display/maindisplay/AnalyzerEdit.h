#ifndef ANALYZEREDIT_H
#define ANALYZEREDIT_H

#include <QTextEdit>

namespace analyzer{
  namespace interpreter{
    class Interpreter;
  }
  namespace gui{
    namespace display{
      class AnalyzerEdit : public QTextEdit
      {
      public:
        AnalyzerEdit(QWidget * parent = 0);
        virtual ~AnalyzerEdit();

        void SetInterpreter(interpreter::Interpreter * interpreter);
      };
    }
  }
}
#endif