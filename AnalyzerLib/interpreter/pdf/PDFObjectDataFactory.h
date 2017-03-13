/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef PDFOBJECTDATAFACTORY_H
#define PDFOBJECTDATAFACTORY_H

#include <memory>
#include <vector>

#include "PDFObjectData.h"

namespace analyzer {
  namespace interpreter {
    class PDFObjectDataFactory
    {
    public:
      static std::unique_ptr<PDFObjectData> CreatePDFObjectData(const std::shared_ptr<std::vector<unsigned char>>, const size_t dataOffset, const size_t & objectOffset);
    };
  }
}

#endif