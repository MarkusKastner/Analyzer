/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "BinaryListView.h"

namespace analyzer {
  namespace gui {
    BinaryListView::BinaryListView(QWidget * parent)
      :QTableView(parent), model()
    {
      this->setup();
    }

    BinaryListView::~BinaryListView()
    {
    }

    void BinaryListView::AddLine(const std::string & hex, const std::string & binary, const std::string & ascii, const std::string & numerical)
    {
      QList<QStandardItem*> items;
      items.push_back(new Item(hex));
      items.push_back(new Item(binary));
      items.push_back(new Item(ascii));
      items.push_back(new Item(numerical));
      this->model.appendRow(items);
    }

    void BinaryListView::Clear()
    {
      this->model.removeRows(0, this->model.rowCount());
    }

    void BinaryListView::setup()
    {
      this->setModel(&this->model);
      QStringList header;
      header << tr("Hex") << tr("Binary") << tr("ASCII") << tr("Integral");
      this->model.setHorizontalHeaderLabels(header);
    }
  }
}