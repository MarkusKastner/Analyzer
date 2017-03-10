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
        :QPlainTextEdit(parent), file(nullptr), highlighter(nullptr), lastBlockText(), hlThread()
      {
        this->lineNumbers = new LineNumberArea(this);
        this->setLineWrapMode(QPlainTextEdit::LineWrapMode::NoWrap);

        connect(this, &AnalyzerEdit::blockCountChanged, this, &AnalyzerEdit::updateLineNumberAreaWidth);
        connect(this, &AnalyzerEdit::updateRequest, this, &AnalyzerEdit::updateLineNumberArea);
        connect(this, &AnalyzerEdit::cursorPositionChanged, this, &AnalyzerEdit::highlightCurrentLine);

        
        
      }

      AnalyzerEdit::~AnalyzerEdit()
      {

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
          }
        }

        if (dynamic_cast<SetHighlighterEvent*>(evt)) {
          this->highlighter = new AnalyzerEditHighlighter(this->document());
          this->highlighter->SetFunctionalHighlightExpressions(dynamic_cast<SetHighlighterEvent*>(evt)->GetExpressions());
          this->hlThread->join();
          this->hlThread.reset();
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
        this->setPlainText(QString::fromLatin1(this->file->GetText().c_str()));
        this->hlThread.reset(new std::thread(&AnalyzerEdit::setHighlighter, this, file->GetText(), this->file->GetFileFormat()));
      }

      void AnalyzerEdit::clearFile()
      {
        this->setPlainText("");
        if (this->file != nullptr) {
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

        QString currentBlockText(this->textCursor().block().text());
        if (currentBlockText.compare(this->lastBlockText) != 0) {
          this->lastBlockText = currentBlockText;
          this->SetBinaryOutput(this->lastBlockText);
        }
        
        this->setExtraSelections(extraSelections);
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

      void AnalyzerEdit::setHighlighter(std::string text, core::FileFormat fileFormat)
      {
        std::vector<std::string> expressions;

        switch (fileFormat) {
        case core::FileFormat::xml:
          expressions = AnalyzerEdit::findXMLExpressions(text);
          break;
        }

        QApplication::postEvent(this, new SetHighlighterEvent(expressions));
      }

      std::vector<std::string> AnalyzerEdit::findXMLExpressions(const std::string & text)
      {
        std::vector<std::string> expressions;
        for (size_t i = 0; i < text.size(); ++i) {
          if (text.at(i) == '<') {
            size_t offset = AnalyzerEdit::findNextOffset(text, i);
            if (offset > text.size()) {
              break;
            }
            AnalyzerEdit::addExpression(expressions, text.substr(i, offset - i + 1));
            i = offset;
          }
        }
        expressions.push_back(">");
        return expressions;
      }

      size_t AnalyzerEdit::findNextOffset(const std::string & text, const size_t i)
      {
        size_t offsetSpace = text.find(' ', i + 1);
        size_t offsetEnd = text.find('>', i + 1);

        if (offsetSpace < offsetEnd) {
          return offsetSpace;
        }
        else {
          return  offsetEnd;
        }
      }

      void AnalyzerEdit::addExpression(std::vector<std::string>& expressions, const std::string & newExpression)
      {
        for (auto& exisiting : expressions) {
          if (exisiting.compare(newExpression) == 0) {
            return;
          }
        }
        expressions.push_back(newExpression);
      }
    }
  }
}