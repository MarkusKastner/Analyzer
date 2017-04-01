/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef BINARYLISTVIEW_H
#define BINARYLISTVIEW_H

#include <QTableView>
#include <QStandardItemModel>
#include <QStandardItem>

namespace analyzer {
  namespace gui {
    class BinaryListView : public QTableView
    {
    private:
      BinaryListView() {}
      class Item : public QStandardItem
      {
      public:
        explicit Item(const std::string & text)
          :QStandardItem(QString::fromLatin1(text.c_str())), text(text)
        {
          this->setup();
        }

        virtual ~Item() {
        }

        virtual QStandardItem *clone() const {
          return new Item(this->text);
        }

        void setup() {

        }
      private:
        std::string text;
      };

    public:
      explicit BinaryListView(QWidget * parent = nullptr);
      virtual ~BinaryListView();

      void AddLine(const std::string & hex, const std::string & binary, const std::string & ascii, const std::string & numerical);
      void Clear();

    private:
      QStandardItemModel model;
      void setup();
    };
  }
}

#endif