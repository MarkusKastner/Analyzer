#include "AnalyzeDock.h"

namespace analyzer {
  namespace gui {
    AnalyzeDock::AnalyzeDock(QWidget *parent, Qt::WindowFlags flags)
      :QDockWidget(tr("Analyze"), parent, flags)
    {
      this->setup();
    }

    AnalyzeDock::~AnalyzeDock()
    {
    }

    void AnalyzeDock::setup()
    {
    }
  }
}