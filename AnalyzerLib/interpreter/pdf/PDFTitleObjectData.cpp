/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "PDFTitleObjectData.h"

namespace analyzer {
  namespace interpreter {
    PDFTitleObjectData::PDFTitleObjectData()
    {
    }

    PDFTitleObjectData::~PDFTitleObjectData()
    {
    }

    std::string PDFTitleObjectData::Data2String()
    {
      return std::string("<p>Title: </p>");
    }

    PDFObjectData * PDFTitleObjectData::Clone()
    {
      return new PDFTitleObjectData(*this);
    }
  }
}