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
        :QPlainTextEdit(parent), file(nullptr), highlighter(nullptr)
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
        QApplication::postEvent(this, new EditEvent());
      }

      void AnalyzerEdit::SetFile(core::File * file)
      {
        this->ClearFile();
        if (file != nullptr){
          this->file = file;
          this->file->RegisterObserver(this);
          this->setPlainText(QString::fromWCharArray(this->file->GetText().c_str()));
        }
      }

      void AnalyzerEdit::ClearFile()
      {
        this->setPlainText("");
        if (this->file != nullptr){
          this->file->UnregisterObserver(this);
        }
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

      void AnalyzerEdit::customEvent(QEvent * evt)
      {
        if (dynamic_cast<EditEvent*>(evt)){
          this->setPlainText(QString::fromWCharArray(this->file->GetText().c_str()));
        }
      }

      void AnalyzerEdit::resizeEvent(QResizeEvent *e)
      {
        QPlainTextEdit::resizeEvent(e);

        QRect cr = contentsRect();
        lineNumbers->setGeometry(QRect(cr.left(), cr.top(), this->GetLineNumbersWidth(), cr.height()));
      }

      void AnalyzerEdit::highlightCurrentLine()
      {
        QList<QTextEdit::ExtraSelection> extraSelections;

        if (!isReadOnly()) {
          QTextEdit::ExtraSelection selection;

          QColor lineColor = QColor(Qt::yellow).lighter(160);

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