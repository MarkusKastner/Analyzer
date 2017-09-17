/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef HEXBROWSER_H
#define HEXBROWSER_H

#include "ViewOutput.h"
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>

#include <vector>
#include <string>

#include "AnalyzerLib\core\File.h"
#include "AnalyzerLib\base\BaseData.h"

class QTableWidget;
class QTableWidgetItem;

namespace analyzer {
  namespace interpreter {
    class HEXInterpreter;
  }
  namespace core {
    class File;
  }
  namespace gui {
    namespace display {
      class HexTableWidget;
      class HexBrowser : public QWidget, public ViewOutput
      {
        Q_OBJECT
      public:
        HexBrowser(QWidget * parent = 0);
        virtual ~HexBrowser();

        virtual void SetFile(core::File * file);
        virtual void ClearFile();

        void AddHexRow(const interpreter::HEXInterpreter::HexRow & hexExp);

        void SetIntegerValue(const int & integerValue);
        void SetDoubleValue(const double & doubleValue);
        void SetWideCharacter(const wchar_t & wideCharacter);
        void SetRGB(const char & r, const char & g, const char & b);

        void ClearValues();

      signals:
        void SetBinaryOutput(const std::vector<unsigned char> & data);

      private:
        HexTableWidget * tableWidget;
        QTableWidget * castTable;

        QTableWidgetItem * integerCast;
        QTableWidgetItem * doubleCast;
        QTableWidgetItem * wideCharacter;
        
        core::File * file;

        void setup();
        void createCastTable();

        class RGBWidget : public QWidget
        {
        public:
          RGBWidget() : QWidget(), color(new QLabel()), rEdit(new QLineEdit()), gEdit(new QLineEdit()), bEdit(new QLineEdit())
          {
            this->color->setAutoFillBackground(true);
            this->setLayout(new QVBoxLayout());
            this->layout()->addWidget(this->color);
            this->layout()->addWidget(this->rEdit);
            this->layout()->addWidget(this->gEdit);
            this->layout()->addWidget(this->bEdit);
            
            this->Clear();
          }
          virtual ~RGBWidget() {}

          void SetValues(const char & r, const char & g, const char & b) {
            
            this->color->setStyleSheet("QLabel { background-color: rgb(" + QString::number(r) + ", " + QString::number(g) + ", " + QString::number(b) + "); }");

            this->rEdit->setText(QString::number(r));
            this->gEdit->setText(QString::number(g));
            this->bEdit->setText(QString::number(b));
          }

          void Clear() {
            this->color->setStyleSheet("QLabel { background-color: rgb(255, 255, 255); }");
            this->rEdit->setText("");
            this->gEdit->setText("");
            this->bEdit->setText("");
          }

        private:
          QLabel * color;
          QLineEdit * rEdit;
          QLineEdit * gEdit;
          QLineEdit * bEdit;
        };
        RGBWidget * rgb;

      };
    }
  }
}
#endif
