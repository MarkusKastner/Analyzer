#include "AnalyzerEdit.h"

#include "AnalyzerLib\interpreter\Interpreter.h"

namespace analyzer{
  namespace gui{
    namespace display{

      AnalyzerEdit::AnalyzerEdit(QWidget * parent)
        :QTextEdit(parent), interpreter(nullptr)
      {

      }
      AnalyzerEdit::~AnalyzerEdit()
      {

      }
      
      void AnalyzerEdit::NotifyDataChanged()
      {
        this->setText(this->interpreter->GetPlainText().c_str());
      }

      void AnalyzerEdit::SetInterpreter(interpreter::Interpreter * interpreter)
      {
        if (this->interpreter != nullptr){
          this->interpreter->UnregisterObserver(this);
        }
        this->interpreter = interpreter;
        if (interpreter != nullptr){
          this->interpreter->RegisterObserver(this);
        }
      }
    }
  }
}