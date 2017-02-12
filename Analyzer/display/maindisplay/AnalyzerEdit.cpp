/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "AnalyzerEdit.h"

#include <QApplication>
#include <QPainter>
#include <QPaintEvent>
#include <QTextBlock>

#include "AnalyzerLib\interpreter\Interpreter.h"
#include "AnalyzerEditHighlighter.h"

namespace analyzer{
  namespace gui{
    namespace display{

      AnalyzerEdit::AnalyzerEdit(QWidget * parent)
        :QPlainTextEdit(parent), file(nullptr), highlighter(nullptr), interpreterDeleted(false)
      {
        this->lineNumbers = new LineNumberArea(this);
        this->setLineWrapMode(QPlainTextEdit::LineWrapMode::NoWrap);

        connect(this, &AnalyzerEdit::blockCountChanged, this, &AnalyzerEdit::updateLineNumberAreaWidth);
        connect(this, &AnalyzerEdit::updateRequest, this, &AnalyzerEdit::updateLineNumberArea);
        connect(this, &AnalyzerEdit::cursorPositionChanged, this, &AnalyzerEdit::highlightCurrentLine);

        this->highlighter = new AnalyzerEditHighlighter(this->document());
        
      }

      AnalyzerEdit::~AnalyzerEdit()
      {

      }
      
      void AnalyzerEdit::NotifyDataChanged()
      {
        QApplication::postEvent(this, new EditEvent(EditEvent::Action::dataChange));
      }

      void AnalyzerEdit::NotifyExInterpreter()
      {
        QApplication::postEvent(this, new EditEvent(EditEvent::Action::exInterpreter));
      }

      void AnalyzerEdit::SetFile(core::File * file)
      {
        if (file != nullptr){
          if (this->file != nullptr && this->file->GetFileName().compare(file->GetFileName()) == 0){
            return;
          }
          this->arrangeNewFile(file);
        }
      }

      void AnalyzerEdit::ClearFile()
      {
        QApplication::postEvent(this, new EditEvent(EditEvent::Action::clear));
      }

      void AnalyzerEdit::LineNumberAreaPaintEvent(QPaintEvent *event)
      {
        QPainter painter(this->lineNumbers);
        painter.fillRect(event->rect(), Qt::lightGray);

        QTextBlock block = this->firstVisibleBlock();
        int blockNumber = block.blockNumber();
        int top = (int)blockBoundingGeometry(block).translated(contentOffset()).top();
        int bottom = top + (int)blockBoundingRect(block).height();

        while (block.isValid() && top <= event->rect().bottom()) {
          if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(Qt::black);
            painter.drawText(0, top, this->lineNumbers->width(), fontMetrics().height(),
              Qt::AlignRight, number);
          }

          block = block.next();
          top = bottom;
          bottom = top + (int)blockBoundingRect(block).height();
          ++blockNumber;
        }
      }

      int AnalyzerEdit::GetLineNumbersWidth()
      {
        int digits = 1;
        int max = qMax(1, this->document()->blockCount());
        while (max >= 10) {
          max /= 10;
          ++digits;
        }

        int space = 3 + fontMetrics().width(QLatin1Char('9')) * digits;

        return space;
      }

      void AnalyzerEdit::SetNewDisplayOptions(const analyzer::base::BaseFormat & baseFormat, const analyzer::base::DetailFormat & detailFormat)
      {
        if (baseFormat == analyzer::base::BaseFormat::text){
          if (detailFormat == analyzer::base::DetailFormat::xml){
            this->highlighter->SetMode(AnalyzerEditHighlighter::Mode::xml);
          }
        }
      }

      void AnalyzerEdit::customEvent(QEvent * evt)
      {
        if (dynamic_cast<EditEvent*>(evt)){
          EditEvent * editEvt = dynamic_cast<EditEvent*>(evt);
          switch (editEvt->GetAction()) {
          case EditEvent::Action::dataChange:
            
            break;
          case EditEvent::Action::clear:
            this->clearFile();
            break;
          case EditEvent::Action::exInterpreter:
            this->interpreterDeleted = true;
            break;
          }
        }
      }

      void AnalyzerEdit::resizeEvent(QResizeEvent *e)
      {
        QPlainTextEdit::resizeEvent(e);

        QRect cr = contentsRect();
        lineNumbers->setGeometry(QRect(cr.left(), cr.top(), this->GetLineNumbersWidth(), cr.height()));
      }

      void AnalyzerEdit::arrangeNewFile(core::File * file)
      {
        this->clearFile();
        this->file = file;
        this->interpreterDeleted = false;
      }

      void AnalyzerEdit::clearFile()
      {
        this->setPlainText("");
        if (this->file != nullptr) {
          if (!this->interpreterDeleted) {
          }
          this->file = nullptr;
        }
      }

      void AnalyzerEdit::highlightCurrentLine()
      {
        QList<QTextEdit::ExtraSelection> extraSelections;

        if (!isReadOnly()) {
          QTextEdit::ExtraSelection selection;

          QColor lineColor = QColor(Qt::GlobalColor::cyan).lighter(160);

          selection.format.setBackground(lineColor);
          selection.format.setProperty(QTextFormat::FullWidthSelection, true);
          selection.cursor = textCursor();
          selection.cursor.clearSelection();
          extraSelections.append(selection);
        }

        setExtraSelections(extraSelections);
      }

      void AnalyzerEdit::updateLineNumberAreaWidth(int)
      {
        this->setViewportMargins(this->GetLineNumbersWidth(), 0, 0, 0);
      }

      void AnalyzerEdit::updateLineNumberArea(const QRect &rect, int dy)
      {
        if (dy){
          this->lineNumbers->scroll(0, dy);
        }
        else{
          this->lineNumbers->update(0, rect.y(), this->lineNumbers->width(), rect.height());
        }
        if (rect.contains(viewport()->rect())){
          this->updateLineNumberAreaWidth(0);
        }
      }
    }
  }
}