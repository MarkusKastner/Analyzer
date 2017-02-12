/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "ViewTab.h"

#include <QVBoxLayout>

#include "AnalyzerTab.h"

#include "display\maindisplay\AnalyzerEdit.h"

namespace analyzer {
  namespace gui {
    ViewTab::ViewTab(AnalyzerTab * parent)
      :QWidget(parent), analyzerEdit(nullptr)
    {
      this->setup();
    }

    ViewTab::~ViewTab()
    {
    }

    display::AnalyzerEdit * ViewTab::GetAnalyzerEdit()
    {
      return this->analyzerEdit;
    }

    void ViewTab::setup()
    {
      this->setLayout(new QVBoxLayout());
      this->layout()->setContentsMargins(1, 1, 1, 1);

      this->analyzerEdit = new display::AnalyzerEdit(this);
      this->layout()->addWidget(this->analyzerEdit);
    }
  }
}