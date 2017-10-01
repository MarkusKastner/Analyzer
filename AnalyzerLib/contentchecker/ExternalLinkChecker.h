/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef EXTERNALLINKCHECKER_H
#define EXTERNALLINKCHECKER_H

#include "ContentChecker.h"

namespace analyzer {
  namespace checker {
    class ExternalLinkChecker : public ContentChecker
    {
    public:
      ExternalLinkChecker();
      virtual ~ExternalLinkChecker();

    protected:
      virtual void checkData();
    };
  }
}
#endif