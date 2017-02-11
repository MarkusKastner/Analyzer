/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "AnalyzerTab.h"
#include "ViewTab.h"
#include "AnalyzeResultTab.h"

namespace analyzer {
  namespace gui {
    AnalyzerTab::AnalyzerTab(QWidget * parent)
     : QTabWidget(parent), viewTab(nullptr), resultTab(nullptr)
    {
      this->setup();
    }

    AnalyzerTab::~AnalyzerTab()
    {
    }

    void AnalyzerTab::setup()
    {
      this->viewTab = new ViewTab(this);
      this->addTab(this->viewTab, tr("View"));
      
      this->resultTab = new AnalyzeResultTab(this);
      this->addTab(this->resultTab, tr("Analyze Result"));
    }
  }
}
