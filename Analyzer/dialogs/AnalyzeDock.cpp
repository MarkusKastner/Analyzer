/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "AnalyzeDock.h"
#include <QVBoxLayout>
#include <QCheckBox>
#include <QPushButton>
#include <QSpacerItem>

namespace analyzer {
  namespace gui {
    AnalyzeDock::AnalyzeDock(QWidget *parent, Qt::WindowFlags flags)
      :QDockWidget(tr("Analyze"), parent, flags),
      extraordinary(nullptr), executable(nullptr), externalLinks(nullptr), macros(nullptr)
    {
      this->setup();
    }

    AnalyzeDock::~AnalyzeDock()
    {
    }

    void AnalyzeDock::SetOptions(const base::AnalyzingOptions & analyzingOptions)
    {
      if (!analyzingOptions.Extraordinary) {
        this->extraordinary->setVisible(false);
      }
      if (!analyzingOptions.Executable) {
        this->executable->setVisible(false);
      }
      if (!analyzingOptions.ExternalLinks) {
        this->externalLinks->setVisible(false);
      }
      if (!analyzingOptions.Macros) {
        this->macros->setVisible(false);
      }
    }

    void AnalyzeDock::ResetOptions()
    {
      this->extraordinary->setVisible(true);
      this->executable->setVisible(true);
      this->externalLinks->setVisible(true);
      this->macros->setVisible(true);
    }

    bool AnalyzeDock::CheckExtraordinary()
    {
      return this->extraordinary->isChecked();
    }

    bool AnalyzeDock::CheckExecutable()
    {
      return this->executable->isChecked();
    }

    bool AnalyzeDock::CheckExternalLinks()
    {
      return this->externalLinks->isChecked();
    }

    bool AnalyzeDock::CheckMacros()
    {
      return this->macros->isChecked();
    }

    void AnalyzeDock::setup()
    {
      this->setLayout(new QVBoxLayout());
      this->layout()->setContentsMargins(1, 1, 1, 1);

      this->setWidget(new QWidget());
      
      this->widget()->setLayout(new QVBoxLayout());
      this->widget()->layout()->setContentsMargins(1, 1, 1, 1);
      this->widget()->layout()->setSpacing(2);

      this->extraordinary = new QCheckBox(tr("Extraordinary Things"), this->widget());
      this->executable = new QCheckBox(tr("Executable Code"), this->widget());
      this->externalLinks = new QCheckBox(tr("External Links"), this->widget());
      this->macros = new QCheckBox(tr("Macros"), this->widget());

      this->widget()->layout()->addWidget(this->extraordinary);
      this->widget()->layout()->addWidget(this->executable);
      this->widget()->layout()->addWidget(this->externalLinks);
      this->widget()->layout()->addWidget(this->macros);
      this->widget()->layout()->addItem(new QSpacerItem(0, 10, QSizePolicy::Expanding, QSizePolicy::Expanding));
      
    }
  }
}