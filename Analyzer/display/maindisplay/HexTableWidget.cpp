/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "HexTableWidget.h"
#include "HexBrowser.h"

#include <sstream>
#include <bitset>
#include <iomanip>

#include <QHeaderView>
#include <QVBoxLayout>
#include <QLabel>
#include <QAbstractButton>

#include "AnalyzerLib\core\File.h"
#include "AnalyzerLib\interpreter\HEXInterpreter.h"

namespace analyzer {
  namespace gui {
    namespace display {
      HexTableWidget::HexTableWidget(HexBrowser * parent)
        :QTableWidget(parent), browser(parent)
      {
        this->setup();
      }

      HexTableWidget::~HexTableWidget()
      {
      }

      void HexTableWidget::SetFile(core::File * file)
      {
        this->file = file;
        auto rows = this->getInterpreter()->GetHexRows();
        for (auto& row : rows) {
          this->AddHexRow(row);
        }
      }

      void HexTableWidget::ClearFile()
      {
      }

      void HexTableWidget::AddHexRow(const std::vector<std::string> & hexExp)
      {
        int numRows = this->rowCount();
        int offset = numRows * 16;
        std::stringstream stream;
        stream << std::setfill('0') << std::setw(10) << std::hex << offset;
        std::string hexStr(stream.str());
        QString offsetStr(stream.str().c_str());
        this->insertRow(numRows);

        this->setVerticalHeaderItem(numRows, new QTableWidgetItem(offsetStr));

        for (size_t i = 0; i < hexExp.size(); i++) {
          this->setItem(numRows, i, new QTableWidgetItem(hexExp[i].c_str()));
          this->item(numRows, i)->setTextAlignment(Qt::Alignment::enum_type::AlignCenter);
        }

      }

      void HexTableWidget::onSelection()
      {
        std::vector<size_t> indexes;

        QList<QTableWidgetItem*> items = this->selectedItems();
        for (auto& item : items) {
          int col = item->column();
          int row = item->row();
          size_t index = col + (row*16);
          indexes.push_back(index);
        }
        auto bytes(this->getInterpreter()->GetBytesByIndex(indexes));
        this->setDetailOutput(bytes);
        this->browser->SetBinaryOutput(bytes);
      }

      void HexTableWidget::setup()
      {
        QStringList horizontal;
        for (int i = 0; i < 16; i++) {
          std::stringstream stream;
          stream << std::setw(2) << std::setfill('0') << std::hex << +i;
          horizontal.push_back(QString(stream.str().c_str()));
          this->insertColumn(i);
          this->setColumnWidth(i, 25);
        }

        this->setHorizontalHeaderLabels(horizontal);
        this->horizontalHeader()->show();
        this->verticalHeader()->show();
        connect(this, &HexTableWidget::itemSelectionChanged, this, &HexTableWidget::onSelection);

      }

      void HexTableWidget::setDetailOutput(const std::vector<unsigned char>& bytes)
      {
        if (bytes.size() > 0) {
          if (bytes.size() == 1) {
            this->browser->SetIntegerValue(static_cast<long long>(bytes[0]));
            return;
          }
          else if(bytes.size() == 2){
            char buffer[2];
            buffer[0] = bytes[0];
            buffer[1] = bytes[1];
            int16_t * value = reinterpret_cast<int16_t*>(&buffer);
            this->browser->SetIntegerValue(*value);
            return;
          }
          else if (bytes.size() == 3) {
            char buffer[3];
            buffer[0] = bytes[0];
            buffer[1] = bytes[1];
            buffer[2] = bytes[2];
            int32_t * value = reinterpret_cast<int32_t*>(&buffer);
            this->browser->SetIntegerValue(static_cast<long long>(*value));
            return;
          }
          else if (bytes.size() == 4) {
            short value = reinterpret_cast<int32_t>(&bytes[0]);
            this->browser->SetIntegerValue(static_cast<long long>(value));
            return;
          }
        }

        this->browser->SetIntegerValue(0);
        this->browser->SetDoubleValue(0.0);

      }

      interpreter::HEXInterpreter * HexTableWidget::getInterpreter()
      {
        return dynamic_cast<interpreter::HEXInterpreter*>(this->file->GetInterpreter().get());
      }
    }
  }
}