/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "AnalyzeResultTab.h"

#include <QVBoxLayout>

#include "AnalyzerTab.h"

namespace analyzer {
  namespace gui {
    AnalyzeResultTab::AnalyzeResultTab(AnalyzerTab * parent)
      :QWidget(parent), textEdit(nullptr)
    {
      this->setup();
    }

    AnalyzeResultTab::~AnalyzeResultTab()
    {
    }

    QTextEdit * AnalyzeResultTab::GetResultTextEdit()
    {
      return this->textEdit;
    }

    void AnalyzeResultTab::Clear()
    {
      this->textEdit->clear();
    }

    void AnalyzeResultTab::setup()
    {
      this->setLayout(new QVBoxLayout());
      this->layout()->setContentsMargins(1, 1, 1, 1);

      this->textEdit = new QTextEdit(this);
      this->layout()->addWidget(this->textEdit);
    }
  }
}