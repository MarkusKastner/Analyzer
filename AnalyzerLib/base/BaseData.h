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
  }
}
#endif