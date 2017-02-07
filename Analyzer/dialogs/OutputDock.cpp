#include "OutputDock.h"

namespace analyzer {
  namespace gui {
    OutputDock::OutputDock(QWidget *parent, Qt::WindowFlags flags)
      :QDockWidget(tr("Output"), parent, flags)
    {
      this->setup();
    }

    OutputDock::~OutputDock()
    {
    }

    void OutputDock::setup()
    {
    }
  }
}