/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

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

    base::DetailFormat DisplayOptionsBinary::GetFormat()
    {
      if (this->binary->isChecked()){
        return base::DetailFormat::bits;
      }
      else if(this->hex->isChecked()){
        return base::DetailFormat::hex;
      }
      else{
        return base::DetailFormat::bits;
      }
    }

    void DisplayOptionsBinary::SetInterpreterOptions(const std::vector<base::DetailFormat> & options)
    {
      this->binary->setVisible(false);
      this->hex->setVisible(false);
      for (auto& option : options) {
        switch (option) {
        case base::DetailFormat::bits:
          this->binary->setVisible(true);
          break;
        case base::DetailFormat::hex:
          this->hex->setVisible(true);
          break;
        }
      }
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

      this->binary->setVisible(false);
      this->hex->setVisible(false);

      connect(this->binary, &QRadioButton::clicked, this, &DisplayOptionsBinary::onOptionsChange);
      connect(this->hex, &QRadioButton::clicked, this, &DisplayOptionsBinary::onOptionsChange);
    }

    void DisplayOptionsBinary::onOptionsChange()
    {
      this->DisplayOptionsChanged();
    }
  }
}