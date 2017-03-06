/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "BinaryDock.h"
#include "BinaryListView.h"

#include <QVBoxLayout>
#include <QApplication>

namespace analyzer {
  namespace gui {
    BinaryDock::BinaryDock(QWidget *parent, Qt::WindowFlags flags)
      :QDockWidget(tr("Binary View"), parent, flags), listView(nullptr)
    {
      this->setup();
    }

    BinaryDock::~BinaryDock()
    {
    }

    void BinaryDock::AddLine(const std::string & hex, const std::string & binary, const std::string & ascii, const std::string & numerical)
    {
      QApplication::postEvent(this, new AddLineEvent(hex, binary, ascii, numerical));
    }

    void BinaryDock::AddLine(const std::string & ascii)
    {
      this->asciiToBinary(ascii);
    }

    void BinaryDock::Clear()
    {
      QApplication::postEvent(this, new ClearEvent());
    }

    void BinaryDock::setup()
    {
      this->setWidget(new QWidget());
      this->widget()->setLayout(new QVBoxLayout());
      this->widget()->layout()->setContentsMargins(1, 1, 1, 1);

      this->listView = new BinaryListView(this->widget());
      this->widget()->layout()->addWidget(this->listView);
    }

    void BinaryDock::asciiToBinary(const std::string & ascii)
    {
    }

    void BinaryDock::customEvent(QEvent * evt)
    {
      if (dynamic_cast<AddLineEvent*>(evt)) {
        auto alEvent = dynamic_cast<AddLineEvent*>(evt);
        this->listView->AddLine(alEvent->GetHex(), alEvent->GetBin(), alEvent->GetASCII(), alEvent->GetNum());
      }
      else if (dynamic_cast<ClearEvent*>(evt)) {
        this->listView->Clear();
      }
    }
  }
}