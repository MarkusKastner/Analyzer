/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef BASICTYPE_H
#define BASICTYPE_H

#if _USRDLL
#define IMEX __declspec(dllexport)
#else
#define IMEX __declspec(dllimport)
#endif

#include <string>

namespace analyzer{
  namespace core{
    class IMEX BasicType
    {
    public:
      virtual ~BasicType();

      virtual unsigned int GetBitAt(const unsigned int & index) = 0;
      virtual std::string GetBitsAsString() = 0;

    protected:
      BasicType();

    };
  }
}
#endif