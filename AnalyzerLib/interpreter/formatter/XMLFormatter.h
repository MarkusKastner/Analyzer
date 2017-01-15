/* Copyright (C) 2016 - 2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef XMLFORMATTER_H
#define XMLFORMATTER_H

#include "Formatter.h"

namespace analyzer{
  namespace interpreter{
    class XMLFormatter : public Formatter
    {
    public:
      XMLFormatter();
      virtual ~XMLFormatter();

      virtual std::shared_ptr<std::wstring> GetText();

    private:
      std::wstring * tabs;
      std::wstring getDataAsWString();

      void increaseTabs();
      void decreaseTabs();
    };
  }
}

#endif