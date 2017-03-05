#include "HTMLOutput.h"

#include "AnalyzerLib\core\File.h"

namespace analyzer {
  namespace gui {
    namespace display {
      HTMPOutput::HTMPOutput(QWidget * parent)
        :QTextEdit(), file(nullptr)
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