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

#include "AnalyzerLib\core\File.h"
#include "AnalyzerLib\interpreter\HEXInterpreter.h"

namespace analyzer {
  namespace gui {
    namespace display {
      HexBrowser::HexBrowser(QWidget * parent)
        :QTableWidget(parent)
      {
        this->setup();
      }

      HexBrowser::~HexBrowser()
      {
      }

      void HexBrowser::SetFile(core::File * file)
      {
        this->file = file;
        auto rows = this->getInterpreter()->GetHexRows();
        for (auto& row : rows) {
          this->AddHexRow(row);
        }
      }

      void HexBrowser::ClearFile()
      {
      }

      void HexBrowser::AddHexRow(const std::vector<std::string> & hexExp)
      {
        int numRows = this->rowCount();
        int offset = numRows * 16;
        std::stringstream stream;
        //stream.setf(std::ios::hex);
        stream << std::setfill('0') << std::setw(10) << std::hex << offset;
        std::string hexStr(stream.str());
        QString offsetStr(stream.str().c_str());
        this->insertRow(numRows);

        this->setItem(numRows, 0, new QTableWidgetItem(offsetStr));
        this->item(numRows, 0)->setTextAlignment(Qt::Alignment::enum_type::AlignCenter);

        for (size_t i = 0; i < hexExp.size(); i++) {
          this->setItem(numRows, i + 1, new QTableWidgetItem(hexExp[i].c_str()));
          this->item(numRows, i + 1)->setTextAlignment(Qt::Alignment::enum_type::AlignCenter);
        }

      }

      void HexBrowser::onSelection()
      {
        std::vector<size_t> indexes;

        QList<QTableWidgetItem*> items = this->selectedItems();
        for (auto& item : items) {
          int col = item->column();
          int row = item->row();
          size_t index = col-1 + (row*16);
          indexes.push_back(index);
        }
        auto bytes(this->getInterpreter()->GetBytesByIndex(indexes));
        this->SetBinaryOutput(bytes);
      }

      void HexBrowser::setup()
      {
        QStringList horizontal;
        horizontal.push_back("offset [h]");
        this->insertColumn(0);
        for (int i = 0; i < 16; i++) {
          std::stringstream stream;
          stream << std::setw(2) << std::setfill('0') << std::hex << +i;
          horizontal.push_back(QString(stream.str().c_str()));
          this->insertColumn(i + 1);
          this->setColumnWidth(i + 1, 25);
        }

        this->setHorizontalHeaderLabels(horizontal);
        this->horizontalHeader()->show();
        this->verticalHeader()->hide();
        connect(this, &HexBrowser::itemSelectionChanged, this, &HexBrowser::onSelection);
      }

      interpreter::HEXInterpreter * HexBrowser::getInterpreter()
      {
        return dynamic_cast<interpreter::HEXInterpreter*>(this->file->GetInterpreter().get());
      }
    }
  }
}