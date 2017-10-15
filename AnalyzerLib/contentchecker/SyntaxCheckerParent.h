/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef SYNTAXHECKERPARENT_H
#define SYNTAXHECKERPARENT_H

#include <vector>
#include <memory>

namespace analyzer {
  namespace checker {
    class SyntaxCheckerParent
    {
    public:
      virtual void SetLastFoundSyntaxOffset(const size_t & offset) = 0;
      virtual const std::shared_ptr<std::vector<unsigned char>> & GetData() const = 0;
    };
  }
}
#endif