/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <memory>
#include <string>
#include <vector>

#include "AnalyzerLib\base\BaseData.h"

namespace analyzer{
  namespace interpreter{
    class TextChangedObserver;
    class TextGlyph;
    class Interpreter
    {
    public:
      virtual bool HasData() = 0;
      virtual void ResetData(const std::shared_ptr<std::vector<unsigned char>> & data) = 0;
      virtual std::shared_ptr<std::vector<unsigned char>> GetData() = 0;
    };
  }
}
#endif