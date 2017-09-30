/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef CONTENTCHECKER_H
#define CONTENTCHECKER_H

namespace analyzer {
  namespace checker {
    class ContentChecker
    {
    public:
      virtual ~ContentChecker();

    protected:
      ContentChecker();
    };
  }
}
#endif