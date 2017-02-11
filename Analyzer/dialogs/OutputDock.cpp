/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "OutputDock.h"

#include <QHBoxLayout>

namespace analyzer {
  namespace gui {
    OutputDock::OutputDock(QWidget *parent, Qt::WindowFlags flags)
      :QDockWidget(tr("Output"), parent, flags), output(nullptr)
    {
      this->setup();
    }

    OutputDock::~OutputDock()
    {
    }

    void OutputDock::AddMessage(const std::string & message)
    {
      this->output->append(QString::fromStdString(message));
    }

    void OutputDock::Clear()
    {
      this->output->clear();
    }

    void OutputDock::setup()
    {
      this->setLayout(new QHBoxLayout());
      this->output = new QTextEdit(this);
      this->setWidget(this->output);
    }
  }
}