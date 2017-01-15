/* Copyright (C) 2016 - 2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "DisplayOptions.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>

namespace analyzer{
  namespace gui{

    DisplayOptions::DisplayOptions(QWidget * parent)
      : QWidget(parent), textMode(nullptr), binaryMode(nullptr),
      binaryOptions(nullptr), textOptions(nullptr)
    {
      this->setup();

    }

    DisplayOptions::~DisplayOptions()
    {

    }

    base::BaseFormat DisplayOptions::GetBaseFormat()
    {
      if (this->textMode->isChecked()){
        return base::BaseFormat::text;
      }
      else{
        return base::BaseFormat::binary;
      }
    }

    base::DetailFormat DisplayOptions::GetDetailedFormat()
    {
      if (this->textMode->isChecked()){
        return this->textOptions->GetFormat();
      }
      else{
        return this->binaryOptions->GetFormat();
      }
    }

    void DisplayOptions::setup()
    {
      this->setLayout(new QVBoxLayout());
      this->setMinimumWidth(150);

      QGroupBox * groupBox = new QGroupBox();
      groupBox->setLayout(new QHBoxLayout());

      this->layout()->addWidget(groupBox);

      this->textMode = new QRadioButton(tr("text"), this);
      this->binaryMode = new QRadioButton(tr("binary"), this);

      groupBox->layout()->addWidget(this->textMode);
      groupBox->layout()->addWidget(this->binaryMode);

      this->binaryOptions = new DisplayOptionsBinary(this);
      this->textOptions = new DisplayOptionsText(this);
      this->layout()->addWidget(this->binaryOptions);
      this->layout()->addWidget(this->textOptions);

      this->layout()->addItem(new QSpacerItem(0, 10, QSizePolicy::Expanding, QSizePolicy::Expanding));

      connect(this->textMode, &QRadioButton::clicked, this, &DisplayOptions::onOptionsChange);
      connect(this->binaryMode, &QRadioButton::clicked, this, &DisplayOptions::onOptionsChange);

      connect(this->binaryOptions, &DisplayOptionsBinary::DisplayOptionsChanged, this, &DisplayOptions::DisplayOptionsChanged);
      connect(this->textOptions, &DisplayOptionsText::DisplayOptionsChanged, this, &DisplayOptions::DisplayOptionsChanged);

      this->textMode->setChecked(true);
      this->onOptionsChange();
    }

    void DisplayOptions::onOptionsChange()
    {
      if (this->textMode->isChecked()){
        this->textOptions->setVisible(true);
        this->binaryOptions->setVisible(false);
      }
      else{
        this->textOptions->setVisible(false);
        this->binaryOptions->setVisible(true);
      }
      this->DisplayOptionsChanged();
    }
  }
}