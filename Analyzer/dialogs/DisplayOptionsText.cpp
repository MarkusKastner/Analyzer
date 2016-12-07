#include "DisplayOptionsText.h"

#include <QHBoxLayout>

namespace analyzer{
  namespace gui{

    DisplayOptionsText::DisplayOptionsText(QWidget * parent)
      : DisplayOptions(parent), plainText(nullptr), pdfMode(nullptr)
    {
      this->setup();
    }

    DisplayOptionsText::~DisplayOptionsText()
    {

    }

    void DisplayOptionsText::setup()
    {
      this->plainText = new QRadioButton(tr("Plain text"), this);
      this->pdfMode = new QRadioButton(tr("PDF mode"), this);
      this->layout()->addWidget(this->plainText);
      this->layout()->addWidget(this->pdfMode);
      this->layout()->addItem(new QSpacerItem(0, 10, QSizePolicy::Expanding, QSizePolicy::Expanding));

      this->plainText->setChecked(true);
    }
  }
}