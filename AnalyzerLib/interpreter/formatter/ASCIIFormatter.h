/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef ASCIIFORMATTER_H
#define ASCIIFORMATTER_H

#include <vector>
#include <string>

namespace analyzer {
  namespace interpreter {
    class ASCIIFormatter 
    {
    public:
      static std::vector<std::string> Split(const std::string & text, const size_t & chunkSize);
      static std::string Text2BinaryExpression(const std::string & text);
      static std::string Text2NumericalExpression(const std::string & text);
      static std::string Text2HexExpression(const std::string & text);
    };
  }
}
#endif