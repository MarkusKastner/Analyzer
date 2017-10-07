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
#include <QTableWidgetItem>
#include <QTableWidget>

#include "AnalyzerLib\core\File.h"
#include "AnalyzerLib\interpreter\HEXInterpreter.h"
#include "HexTableWidget.h"

namespace analyzer {
  namespace gui {
    namespace display {
      HexBrowser::HexBrowser(QWidget * parent)
        :QWidget(parent), tableWidget(nullptr), castTable(nullptr), 
        integerCast(new QTableWidgetItem()), doubleCast(new QTableWidgetItem()),
        wideCharacter(new QTableWidgetItem()), rgb(new RGBWidget())
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

      void HexBrowser::AddHexRow(const interpreter::HEXInterpreter::HexRow & hexExp)
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

      void HexBrowser::SetRGB(const unsigned char & r, const unsigned char & g, const unsigned char & b)
      {
        this->rgb->SetValues(r, g, b);
      }

      void HexBrowser::ClearValues()
      {
        this->integerCast->setText("");
        this->doubleCast->setText("");
        this->wideCharacter->setText("");
        this->rgb->Clear();
      }

      void HexBrowser::MarkIndex(const analyzer::base::Marking & marking)
      {
        this->tableWidget->MarkIndex(marking);
      }

      void HexBrowser::DeleteColor(const analyzer::base::AnalyzerRGB & color)
      {
        this->tableWidget->DeleteColor(color);
      }

      void HexBrowser::setup()
      {
        this->setLayout(new QHBoxLayout());

        QWidget * detailWidget = new QWidget(this);
        detailWidget->setLayout(new QVBoxLayout());
        detailWidget->layout()->setContentsMargins(0, 0, 0, 0);
        detailWidget->setFixedWidth(250);
        detailWidget->setFixedHeight(300);

        QGroupBox * details = new QGroupBox("Details", detailWidget);
        details->setLayout(new QVBoxLayout());

        this->createCastTable();
        details->layout()->addWidget(this->castTable);
        detailWidget->layout()->addWidget(details);
        detailWidget->layout()->addItem(new QSpacerItem(1,1, QSizePolicy::Expanding, QSizePolicy::Expanding));
        
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
        verticalHeaderList.push_back("RGB");

        this->castTable = new QTableWidget(this);
        this->castTable->setFixedWidth(230);
        this->castTable->insertColumn(0);
        this->castTable->insertRow(0);
        this->castTable->insertRow(1);
        this->castTable->insertRow(2);
        this->castTable->insertRow(3);

        this->castTable->setHorizontalHeaderLabels(horizontalHeaderList);
        this->castTable->setVerticalHeaderLabels(verticalHeaderList);
        
        this->integerCast->setTextAlignment(Qt::Alignment::enum_type::AlignRight);
        this->doubleCast->setTextAlignment(Qt::Alignment::enum_type::AlignRight);
        this->wideCharacter->setTextAlignment(Qt::Alignment::enum_type::AlignRight);

        this->castTable->setItem(0, 0, this->integerCast);
        this->castTable->setItem(1, 0, this->doubleCast);
        this->castTable->setItem(2, 0, this->wideCharacter);
        this->castTable->setCellWidget(3, 0, this->rgb);

        this->castTable->verticalHeader()->show();
        this->castTable->horizontalHeader()->show();
        this->castTable->setColumnWidth(1, 150);

      }
    }
  }
}