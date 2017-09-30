/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef BASEDATA_H
#define BASEDATA_H

namespace analyzer{
  namespace base{
    enum BaseFormat
    {
      binary = 0,
      text
    };

    enum DetailFormat
    {
      unknown = 0,
      bits,
      hex,
      simpleText,
      xml,
      pdf
    };

    struct AnalyzerRGB
    {
      int r;
      int g;
      int b;
    };
  }
}
#endif