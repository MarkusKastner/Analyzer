#include "AnalyzerEdit.h"

#include <QApplication>

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
        QApplication::postEvent(this, new EditEvent());
      }

      void AnalyzerEdit::SetInterpreter(interpreter::Interpreter * interpreter)
      {
        this->ClearInterpreter();
        if (interpreter != nullptr){
          this->interpreter = interpreter;
          this->interpreter->RegisterObserver(this);
          this->setText(this->interpreter->GetPlainText().c_str());
        }
      }

      void AnalyzerEdit::ClearInterpreter()
      {
        this->setText("");
        if (this->interpreter != nullptr){
          this->interpreter->UnregisterObserver(this);
        }
      }
      void AnalyzerEdit::customEvent(QEvent * evt)
      {
        if (dynamic_cast<EditEvent*>(evt)){
          this->setText(this->interpreter->GetPlainText().c_str());
        }
      }
    }
  }
}