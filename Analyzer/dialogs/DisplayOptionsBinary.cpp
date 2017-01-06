#include "DisplayOptionsBinary.h"

#include <QVBoxLayout>

namespace analyzer{
  namespace gui{

    DisplayOptionsBinary::DisplayOptionsBinary(QWidget * parent)
      : QWidget(parent), binary(nullptr), hex(nullptr)
    {
      this->setup();
    }

    DisplayOptionsBinary::~DisplayOptionsBinary()
    {

    }

    void DisplayOptionsBinary::setup()
    {
      this->setLayout(new QVBoxLayout());
      this->binary = new QRadioButton(tr("Plain bits"), this);
      this->hex = new QRadioButton(tr("Hex"), this);
      this->layout()->addWidget(this->binary);
      this->layout()->addWidget(this->hex);
      this->layout()->addItem(new QSpacerItem(0, 10, QSizePolicy::Expanding, QSizePolicy::Expanding));

      this->binary->setChecked(true);
    }
  }
}