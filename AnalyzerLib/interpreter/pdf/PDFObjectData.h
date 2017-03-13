/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef PDFOBJECTDATA_H
#define PDFOBJECTDATA_H

#include <string>

namespace analyzer {
  namespace interpreter {
    class PDFObjectData
    {
    public:
      virtual ~PDFObjectData() {}
      virtual std::string Data2String() = 0;
      virtual PDFObjectData * Clone() = 0;

    protected:
      PDFObjectData() {}
    };
  }
}

#endif