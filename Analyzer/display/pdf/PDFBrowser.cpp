/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "PDFBrowser.h"

#include <QTextBlock>

#include "AnalyzerLib\interpreter\pdf\PDFInterpreter.h"

namespace analyzer {
  namespace gui {
    namespace display {
      PDFBrowser::PDFBrowser(QWidget * parent)
        :QTextEdit(parent), file(nullptr)
      {
      }

      PDFBrowser::~PDFBrowser()
      {
      }

      void PDFBrowser::SetFile(core::File * file)
      {
        this->file = file;
        this->setText(QString::fromLatin1(this->file->GetText().c_str()));
      }

      void PDFBrowser::ClearFile()
      {
      }

      void PDFBrowser::mousePressEvent(QMouseEvent * evt)
      {
        QTextEdit::mousePressEvent(evt);

        std::string block(this->textCursor().block().text().toStdString());

        if (block.empty() || block.size() < 3) {
          return;
        }
        if (block.at(0) == '+' || block.at(0) == '-') {
          size_t start = block.find(' ') + 1;
          size_t offset = block.size() - start;

          std::string name = block.substr(start, offset);

          dynamic_cast<interpreter::PDFInterpreter*>(this->file->GetInterpreter().get())->SwitchFolding(name);

          this->setText(QString::fromLatin1(this->file->GetText().c_str()));
        }
      }
    }
  }
}
