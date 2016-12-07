#include "DisplayOptionsBinary.h"

#include <QHBoxLayout>

namespace analyzer{
  namespace gui{

    DisplayOptionsBinary::DisplayOptionsBinary(QWidget * parent)
      : DisplayOptions(parent), plainBits(nullptr), hex(nullptr)
    {
      this->setup();
    }

    DisplayOptionsBinary::~DisplayOptionsBinary()
    {

    }

    void DisplayOptionsBinary::setup()
    {
      this->plainBits = new QRadioButton(tr("Plain bits"), this);
      this->hex = new QRadioButton(tr("Hex"), this);
      this->layout()->addWidget(this->plainBits);
      this->layout()->addWidget(this->hex);
      this->layout()->addItem(new QSpacerItem(0, 10, QSizePolicy::Expanding, QSizePolicy::Expanding));

      this->plainBits->setChecked(true);
    }
  }
}