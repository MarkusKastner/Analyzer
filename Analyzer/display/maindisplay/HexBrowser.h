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
        void SetRGB(const unsigned char & r, const unsigned char & g, const unsigned char & b);

        void ClearValues();

        void MarkIndex(const analyzer::base::Marking & marking);
        void DeleteColor(const analyzer::base::AnalyzerRGB & color);

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
          RGBWidget() : QWidget(), color(new QLabel()), rLabel(new QLabel()), gLabel(new QLabel()), bLabel(new QLabel())
          {
            this->color->setFixedSize(30, 20);
            this->color->setAutoFillBackground(true);
            this->setLayout(new QHBoxLayout());
            this->layout()->addWidget(this->color);
            this->layout()->addWidget(this->rLabel);
            this->layout()->addWidget(this->gLabel);
            this->layout()->addWidget(this->bLabel);
            this->layout()->setContentsMargins(1, 1, 1, 1);
            
            this->Clear();
          }
          virtual ~RGBWidget() {}

          void SetValues(const unsigned char & r, const unsigned char & g, const unsigned char & b) {
            
            QString styleString("background:rgb(" + QString::number(r) + ", " + QString::number(g) + ", " + QString::number(b) + ");");
            this->color->setStyleSheet(styleString);

            this->rLabel->setText(QString::number(r));
            this->gLabel->setText(QString::number(g));
            this->bLabel->setText(QString::number(b));
          }

          void Clear() {
            this->color->setStyleSheet("QLabel { background-color: rgb(255, 255, 255); }");
            this->rLabel->setText("");
            this->gLabel->setText("");
            this->bLabel->setText("");
          }

        private:
          QLabel * color;
          QLabel * rLabel;
          QLabel * gLabel;
          QLabel * bLabel;
        };
        RGBWidget * rgb;

      };
    }
  }
}
#endif
