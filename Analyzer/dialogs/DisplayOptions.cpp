#include "DisplayOptions.h"
#include <QLabel>
#include <QVBoxLayout>

namespace analyzer{
  namespace gui{

    DisplayOptions::DisplayOptions(QWidget * parent)
      : QWidget(parent)
    {
      this->setLayout(new QVBoxLayout());
      this->setMinimumWidth(150);
    }

    DisplayOptions::~DisplayOptions()
    {

    }
  }
}