#ifndef ANALYZEREDIT_H
#define ANALYZEREDIT_H

#include <QPlainTextEdit>
#include <QEvent>

#include "AnalyzerLib\interpreter\TextChangedObserver.h"
#include "AnalyzerLib\core\File.h"

class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;

class LineNumberArea;

namespace analyzer{
  namespace interpreter{
    class Interpreter;
  }
  namespace gui{
    namespace display{
      class AnalyzerEditHighlighter;
      class AnalyzerEdit : public QPlainTextEdit, public interpreter::TextChangedObserver
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

        void SetFile(core::File * file);
        void ClearFile();

        void LineNumberAreaPaintEvent(QPaintEvent *event);
        int GetLineNumbersWidth();

      protected:
        void customEvent(QEvent * evt);
        void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

      private:
        core::File * file;
        QWidget *lineNumbers;
        AnalyzerEditHighlighter * highlighter;

        void highlightCurrentLine();
        void updateLineNumberAreaWidth(int newBlockCount);
        void updateLineNumberArea(const QRect &, int);
      };

      class LineNumberArea : public QWidget
      {
      public:
        LineNumberArea(AnalyzerEdit *editor) : QWidget(editor) {
          codeEditor = editor;
        }

        QSize sizeHint() const Q_DECL_OVERRIDE{
          return QSize(codeEditor->GetLineNumbersWidth(), 0);
        }

      protected:
        void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE{
          codeEditor->LineNumberAreaPaintEvent(event);
        }

      private:
        AnalyzerEdit *codeEditor;
      };
    }
  }
}
#endif