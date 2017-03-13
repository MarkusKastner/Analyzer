/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "PDFObjectDataFactory.h"

namespace analyzer {
  namespace interpreter {
    std::unique_ptr<PDFObjectData> PDFObjectDataFactory::CreatePDFObjectData(const std::shared_ptr<std::vector<unsigned char>>, const size_t dataOffset, const size_t & objectOffset)
    {
      return std::unique_ptr<PDFObjectData>();
    }
  }
}
