/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "PDFBrowser.h"

namespace analyzer {
  namespace gui {
    namespace display {
      PDFBrowser::PDFBrowser(QWindow * parent)
      {
      }

      PDFBrowser::~PDFBrowser()
      {
      }

      void PDFBrowser::mousePressEvent(QMouseEvent * evt)
      {
        QTextEdit::mousePressEvent(evt);
        this->OnClick(evt);
      }
    }
  }
}
