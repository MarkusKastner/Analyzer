/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef HEXTABLEWIDGETITEM_H
#define HEXTABLEWIDGETITEM_H

#include <QTableWidgetItem>

#include <vector>

#include "AnalyzerLib\base\BaseData.h"

namespace analyzer {
  namespace gui {
    namespace display {
      class HexTableWidgetItem : public QTableWidgetItem
      {
      public:
        explicit HexTableWidgetItem(const std::string & expression, const size_t & index) 
          :QTableWidgetItem(expression.c_str()), index(index)
        {

        }
        virtual ~HexTableWidgetItem() {}

        const size_t & GetIndex() const { return this->index; }

        void SetNewColor(const base::AnalyzerRGB & color) {
          this->setBackgroundColor(QColor(color.r, color.g, color.b));
          auto end = this->colors.end();
          for (auto it = this->colors.begin(); it != end; ++it) {
            if ((*it) == color) {
              return;
            }
          }
          this->colors.push_back(color);
        }

        void ClearColor(const base::AnalyzerRGB & color) {
          if (this->colors.empty()) {
            return;
          }
          auto end = this->colors.end();
          for (auto it = this->colors.begin(); it != end; ++it) {
            if ((*it) == color) {
              this->colors.erase(it);
              break;
            }
          }
          if (!this->colors.empty()) {
            this->setBackgroundColor(QColor(this->colors[0].r, this->colors[0].g, this->colors[0].b));
          }
          else {
            this->setBackgroundColor(QColor(0, 0, 0));
          }
        }

        bool HasColor(const base::AnalyzerRGB & color) {
          auto end = this->colors.end();
          for (auto it = this->colors.begin(); it != end; ++it) {
            if ((*it) == color) {
              return true;
            }
          }
          return false;
        }

      private:
        size_t index;
        std::vector<base::AnalyzerRGB> colors;
      };
    }
  }
}
#endif