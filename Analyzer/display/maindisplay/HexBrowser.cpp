/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "HexBrowser.h"

#include <sstream>
#include <bitset>
#include <iomanip>

#include <QHeaderView>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLabel>

#include "AnalyzerLib\core\File.h"
#include "AnalyzerLib\interpreter\HEXInterpreter.h"
#include "HexTableWidget.h"

namespace analyzer {
  namespace gui {
    namespace display {
      HexBrowser::HexBrowser(QWidget * parent)
        :QWidget(parent), tableWidget(nullptr), intLineEdit(nullptr), floatLineEdit(nullptr)
      {
        this->setup();
      }

      HexBrowser::~HexBrowser()
      {
      }

      void HexBrowser::SetFile(core::File * file)
      {
        this->tableWidget->SetFile(file);
      }

      void HexBrowser::ClearFile()
      {
      }

      void HexBrowser::AddHexRow(const std::vector<std::string> & hexExp)
      {
        this->tableWidget->AddHexRow(hexExp);
      }

      void HexBrowser::SetIntegerValue(const int & integerValue)
      {
        this->intLineEdit->setText(QString::number(integerValue));
      }

      void HexBrowser::SetDoubleValue(const double & doubleValue)
      {
        this->floatLineEdit->setText(QString::number(doubleValue));
      }

      void HexBrowser::setup()
      {
        this->setLayout(new QVBoxLayout());

        QWidget * detailWidget = new QWidget(this);
        detailWidget->setLayout(new QVBoxLayout());

        QGroupBox * details = new QGroupBox("Details", detailWidget);
        details->setLayout(new QHBoxLayout());
        
        QWidget * intWidget = new QWidget(details);
        intWidget->setLayout(new QHBoxLayout());
        this->intLineEdit = new QLineEdit(details);
        QLabel * intLabel = new QLabel("Integral: ");
        intWidget->layout()->addWidget(intLabel);
        intWidget->layout()->addWidget(this->intLineEdit);

        QWidget * floatWidget = new QWidget(details);
        floatWidget->setLayout(new QHBoxLayout());
        this->floatLineEdit = new QLineEdit(details);
        QLabel * floatLabel = new QLabel("Floating Point: ");
        floatWidget->layout()->addWidget(floatLabel);
        floatWidget->layout()->addWidget(this->floatLineEdit);

        details->layout()->addWidget(intWidget);
        details->layout()->addWidget(floatWidget);

        detailWidget->layout()->addWidget(details);

        this->tableWidget = new HexTableWidget(this);
        this->layout()->addWidget(detailWidget);
        this->layout()->addWidget(this->tableWidget);
      }
    }
  }
}