#include "DisplayOptionsText.h"

#include <QVBoxLayout>

namespace analyzer{
  namespace gui{

    DisplayOptionsText::DisplayOptionsText(QWidget * parent)
      : QWidget(parent), plainText(nullptr), xmlMode(nullptr), pdfMode(nullptr)
    {
      this->setup();
    }

    DisplayOptionsText::~DisplayOptionsText()
    {

    }

    void DisplayOptionsText::setup()
    {
      this->setLayout(new QVBoxLayout());
      this->plainText = new QRadioButton(tr("Plain text"), this);
      this->xmlMode = new QRadioButton(tr("XML"), this);
      this->pdfMode = new QRadioButton(tr("PDF"), this);
      this->layout()->addWidget(this->plainText);
      this->layout()->addWidget(this->xmlMode);
      this->layout()->addWidget(this->pdfMode);
      this->layout()->addItem(new QSpacerItem(0, 10, QSizePolicy::Expanding, QSizePolicy::Expanding));

      this->plainText->setChecked(true);
      connect(this->plainText, &QRadioButton::clicked, this, &DisplayOptionsText::onOptionsChange);
      connect(this->xmlMode, &QRadioButton::clicked, this, &DisplayOptionsText::onOptionsChange);
      connect(this->pdfMode, &QRadioButton::clicked, this, &DisplayOptionsText::onOptionsChange);
    }

    void DisplayOptionsText::onOptionsChange()
    {
      this->DisplayOptionsChanged();
    }
  }
}