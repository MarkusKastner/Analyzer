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

    base::DetailFormat DisplayOptionsText::GetFormat()
    {
      if (this->plainText->isChecked()){
        return base::DetailFormat::simpleText;
      }
      else if (this->xmlMode->isChecked()){
        return base::DetailFormat::xml;
      }
      else if (this->pdfMode->isChecked()){
        return base::DetailFormat::pdf;
      }
      else{
        return base::DetailFormat::simpleText;
      }
    }

    void DisplayOptionsText::SetInterpreterOptions(const std::vector<base::DetailFormat> & options)
    {
      this->plainText->setVisible(false);
      this->xmlMode->setVisible(false);
      this->pdfMode->setVisible(false);

      for (auto& option : options) {
        switch (option) {
        case base::DetailFormat::simpleText:
          this->plainText->setVisible(true);
          break;
        case base::DetailFormat::xml:
          this->xmlMode->setVisible(true);
          break;
        case base::DetailFormat::pdf:
          this->pdfMode->setVisible(true);
          break;
        }
      }
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

      this->plainText->setVisible(false);
      this->xmlMode->setVisible(false);
      this->pdfMode->setVisible(false);
      
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