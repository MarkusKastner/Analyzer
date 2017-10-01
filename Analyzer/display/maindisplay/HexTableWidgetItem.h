/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef HEXTABLEWIDGETITEM_H
#define HEXTABLEWIDGETITEM_H

#include <QTableWidgetItem>

namespace analyzer {
  namespace gui {
    namespace display {
      class HexTableWidgetItem : public QTableWidgetItem
      {
        //Q_OBJECT
      public:
        explicit HexTableWidgetItem(const std::string & expression, const size_t & index) 
          :QTableWidgetItem(expression.c_str()), index(index)
        {

        }
        virtual ~HexTableWidgetItem() {}

        const size_t & GetIndex() const { return this->index; }

      private:
        size_t index;
      };
    }
  }
}
#endif