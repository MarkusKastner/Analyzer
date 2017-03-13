/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef PDFTITLEOBJECTDATA_H
#define PDFTITLEOBJECTDATA_H

#include <string>
#include "PDFObjectData.h"

namespace analyzer {
  namespace interpreter {
    class PDFTitleObjectData : public PDFObjectData
    {
    public:
      PDFTitleObjectData();
      virtual ~PDFTitleObjectData();
      virtual std::string Data2String();
      virtual PDFObjectData * Clone();
    };
  }
}

#endif