/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef CHECKER_H
#define CHECKER_H

#include "ContentChecker.h"

namespace analyzer {
  namespace checker {
    class ExecutableChecker : public ContentChecker
    {
    public:
      ExecutableChecker();
      virtual ~ExecutableChecker();

    protected:
      virtual void checkData();
    };
  }
}
#endif