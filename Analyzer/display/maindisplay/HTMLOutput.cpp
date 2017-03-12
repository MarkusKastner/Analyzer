/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "HTMLOutput.h"

#include "AnalyzerLib\core\File.h"

namespace analyzer {
  namespace gui {
    namespace display {
      HTMPOutput::HTMPOutput(QWidget * parent)
        :QTextEdit(parent), file(nullptr)
      {
      }

      HTMPOutput::~HTMPOutput()
      {
      }

      void HTMPOutput::SetFile(core::File * file)
      {
        this->file = file;
        this->setText(this->file->GetText().c_str());
      }

      void HTMPOutput::ClearFile()
      {
      }
    }
  }
}