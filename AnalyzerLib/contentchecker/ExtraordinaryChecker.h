/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef EXTRAORDINARYCHECKER_H
#define EXTRAORDINARYCHECKER_H

#include "ContentChecker.h"

namespace analyzer {
  namespace checker {
    class ExtraordinaryChecker : public ContentChecker
    {
    public:
      ExtraordinaryChecker();
      virtual ~ExtraordinaryChecker();

    protected:
      virtual void checkData();
    };
  }
}
#endif