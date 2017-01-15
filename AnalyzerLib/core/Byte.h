/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef BYTE_H
#define BYTE_H

#if _USRDLL
#define IMEX __declspec(dllexport)
#else
#define IMEX __declspec(dllimport)
#endif

#include "BasicType.h"

#include <string>

namespace analyzer{
  namespace core{
    class IMEX Byte : public BasicType
    {
    public:
      static const unsigned int ByteSize = 8;

      Byte();
      explicit Byte(const unsigned char & value);
      virtual ~Byte();

      const unsigned char & GetValue() const;

      virtual unsigned int GetBitAt(const unsigned int & index);
      virtual std::string GetBitsAsString();

    private:
      unsigned char value;
     
    };

    bool operator==(const Byte & b1, const Byte & b2);
  }
}
#endif