/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "BinaryDock.h"
#include "BinaryListView.h"

#include <QVBoxLayout>
#include <QApplication>

#include "AnalyzerLib\interpreter\formatter\ASCIIFormatter.h"

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

    void BinaryDock::SetBinaryOutputFromString(const QString & binary)
    {
      std::vector<std::string> lines = interpreter::ASCIIFormatter::Split(binary.toStdString(), 4);
      for (auto& line : lines) {
        this->AddLine(interpreter::ASCIIFormatter::Text2HexExpression(line),
          interpreter::ASCIIFormatter::Text2BinaryExpression(line),
          line,
          interpreter::ASCIIFormatter::Text2NumericalExpression(line));
      }
    }

    void BinaryDock::SetBinaryOutputFromBytes(const std::vector<unsigned char> & data)
    {
      std::vector<std::vector<unsigned char>> lines;
      int counter = 0;
      std::vector<unsigned char> byteLine;
      for (auto& byte : data) {
        byteLine.push_back(byte);
        counter++;
        if (counter == 4) {
          counter = 0;
          lines.push_back(byteLine);
          byteLine.clear();
        }
      }
      if (!byteLine.empty()) {
        lines.push_back(byteLine);
      }

      for (auto& line : lines) {
        this->AddLine(interpreter::ASCIIFormatter::Bytes2HexExpression(line),
          interpreter::ASCIIFormatter::Bytes2BinaryExpression(line),
          interpreter::ASCIIFormatter::Bytes2ASCIIExpression(line),
          interpreter::ASCIIFormatter::Bytes2NumericalExpression(line));
      }
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