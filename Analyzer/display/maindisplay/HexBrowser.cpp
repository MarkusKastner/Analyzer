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
#include <QTableWidget>
#include <QTableWidgetItem>

#include "AnalyzerLib\core\File.h"
#include "AnalyzerLib\interpreter\HEXInterpreter.h"
#include "HexTableWidget.h"

namespace analyzer {
  namespace gui {
    namespace display {
      HexBrowser::HexBrowser(QWidget * parent)
        :QWidget(parent), tableWidget(nullptr), castTable(nullptr), 
        integerCast(new QTableWidgetItem()), doubleCast(new QTableWidgetItem()),
        wideCharacter(new QTableWidgetItem())
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
        this->integerCast->setText(QString::number(integerValue));
      }

      void HexBrowser::SetDoubleValue(const double & doubleValue)
      {
        this->doubleCast->setText(QString::number(doubleValue));
      }

      void HexBrowser::SetWideCharacter(const wchar_t & wideCharacter)
      {
        this->wideCharacter->setText(QString::fromWCharArray(&wideCharacter, 1));
      }

      void HexBrowser::setup()
      {
        this->setLayout(new QHBoxLayout());

        QWidget * detailWidget = new QWidget(this);
        detailWidget->setLayout(new QVBoxLayout());
        detailWidget->layout()->setContentsMargins(0, 0, 0, 0);
        detailWidget->setMaximumWidth(200);
        detailWidget->setMinimumWidth(200);

        QGroupBox * details = new QGroupBox("Details", detailWidget);
        details->setLayout(new QVBoxLayout());

        this->createCastTable();
        details->layout()->addWidget(this->castTable);
        detailWidget->layout()->addWidget(details);

        this->tableWidget = new HexTableWidget(this);
        this->layout()->addWidget(this->tableWidget);
        this->layout()->addWidget(detailWidget);
        
      }

      void HexBrowser::createCastTable()
      {
        QStringList horizontalHeaderList;
        horizontalHeaderList.push_back("value");

        QStringList verticalHeaderList;
        verticalHeaderList.push_back("Integer");
        verticalHeaderList.push_back("Floating point");
        verticalHeaderList.push_back("Wide character");

        this->castTable = new QTableWidget(this);
        this->castTable->insertColumn(0);
        this->castTable->insertRow(0);
        this->castTable->insertRow(1);
        this->castTable->insertRow(2);

        this->castTable->setHorizontalHeaderLabels(horizontalHeaderList);
        this->castTable->setVerticalHeaderLabels(verticalHeaderList);
        
        this->integerCast->setTextAlignment(Qt::Alignment::enum_type::AlignRight);
        this->doubleCast->setTextAlignment(Qt::Alignment::enum_type::AlignRight);
        this->wideCharacter->setTextAlignment(Qt::Alignment::enum_type::AlignRight);

        this->castTable->setItem(0, 0, this->integerCast);
        this->castTable->setItem(1, 0, this->doubleCast);
        this->castTable->setItem(2, 0, this->wideCharacter);

        this->castTable->verticalHeader()->show();
        this->castTable->horizontalHeader()->show();

        this->castTable->setMaximumWidth(190);
        this->castTable->setMinimumWidth(190);
      }
    }
  }
}