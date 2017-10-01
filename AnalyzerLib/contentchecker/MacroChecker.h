/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef MACROCHECKER_H
#define MACROCHECKER_H

#include "ContentChecker.h"

namespace analyzer {
  namespace checker {
    class MacroChecker : public ContentChecker
    {
    public:
      MacroChecker();
      virtual ~MacroChecker();

    protected:
      virtual void checkData();
    };
  }
}
#endif