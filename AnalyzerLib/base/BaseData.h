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

    struct Marking
    {
      size_t Index;
      AnalyzerRGB Color;
    };
  }
}

inline bool operator==(const analyzer::base::AnalyzerRGB & color1, const analyzer::base::AnalyzerRGB & color2) {
  if (color1.r == color2.r ||
    color1.g == color2.g ||
    color1.b == color2.b) {
    return true;
  }
  else {
    return false;
  }
}
#endif