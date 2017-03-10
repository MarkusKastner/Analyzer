/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef ANALYZEREDIT_H
#define ANALYZEREDIT_H

#include "ViewOutput.h"

#include <QPlainTextEdit>
#include <QEvent>

#include <thread>

#include "AnalyzerLib\core\File.h"
#include "AnalyzerLib\base\BaseData.h"

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
      class AnalyzerEdit : public QPlainTextEdit, public ViewOutput
      {
        Q_OBJECT
      public:
        AnalyzerEdit(QWidget * parent = 0);
        virtual ~AnalyzerEdit();

        virtual void SetFile(core::File * file);
        virtual void ClearFile();

        void LineNumberAreaPaintEvent(QPaintEvent *event);
        int GetLineNumbersWidth();

        void SetNewDisplayOptions(const analyzer::base::BaseFormat & baseFormat, const analyzer::base::DetailFormat & detailFormat);

      signals:
        void SetBinaryOutput(const QString & binary);

      protected:
        void customEvent(QEvent * evt);
        void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

      private:
        core::File * file;
        QWidget * lineNumbers;
        AnalyzerEditHighlighter * highlighter;
        QString lastBlockText;
        std::unique_ptr<std::thread> hlThread;

        class EditEvent : public QEvent
        {
        public:
          enum Action { clear, dataChange };
          EditEvent(const Action & action)
            :QEvent(Type::User), action(action)
          {}

          const Action & GetAction() { return this->action; }
          virtual ~EditEvent() {}

        private:
          Action action;
        };

        class SetHighlighterEvent : public QEvent
        {
        public:
          SetHighlighterEvent(const std::vector<std::string> & expressions)
            :QEvent(static_cast<QEvent::Type>(QEvent::Type::User + 1)), expressions(expressions)
          {}
          virtual ~SetHighlighterEvent() {}
          const std::vector<std::string> & GetExpressions() const { return this->expressions; }
        private:
          std::vector<std::string> expressions;
        };

        void arrangeNewFile(core::File * file);
        void clearFile();

        void highlightCurrentLine();
        void updateLineNumberAreaWidth(int newBlockCount);
        void updateLineNumberArea(const QRect &, int);
        void setHighlighter(std::string text, core::FileFormat fileFormat);

        static std::vector<std::string> findXMLExpressions(const std::string & text);
        static size_t findNextOffset(const std::string & text, const size_t i);
        static void addExpression(std::vector<std::string> & expressions, const std::string & newExpression);
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