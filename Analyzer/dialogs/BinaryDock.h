/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef BINARYDOCK_H
#define BINARYDOCK_H

#include <QDockWidget>
#include <QEvent>

namespace analyzer {
  namespace gui {
    class BinaryListView;
    class BinaryDock : public QDockWidget
    {
    private:
      class AddLineEvent : public QEvent
      {
      public:
        static const QEvent::Type addLineEvent = static_cast<QEvent::Type>(QEvent::Type::User + 1);
        AddLineEvent(const std::string & hex, const std::string & binary, const std::string & ascii, const std::string & numerical)
          : QEvent(addLineEvent), hex(hex), binary(binary), ascii(ascii), numerical(numerical)
        {}

        virtual ~AddLineEvent() {}

        const std::string & GetHex() const { return this->hex; }
        const std::string & GetBin() const { return this->binary; }
        const std::string & GetASCII() const { return this->ascii; }
        const std::string & GetNum() const { return this->numerical; }

      private:
        std::string hex;
        std::string binary;
        std::string ascii;
        std::string numerical;
      };

      class ClearEvent : public QEvent
      {
      public:
        static const QEvent::Type clearEvent = static_cast<QEvent::Type>(QEvent::Type::User + 2);
        ClearEvent() : QEvent(clearEvent) {}
        virtual ~ClearEvent() {}
      };

    public:
      BinaryDock(QWidget *parent = Q_NULLPTR, Qt::WindowFlags flags = Qt::WindowFlags());
      virtual ~BinaryDock();

      void AddLine(const std::string & hex, const std::string & binary, const std::string & ascii, const std::string & numerical);
      void Clear();

    protected:
      void customEvent(QEvent * evt);

    private:
      BinaryListView * listView;

      void setup();
    };
  }
}

#endif