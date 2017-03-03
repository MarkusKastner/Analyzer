/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef BODYELEMENT_H
#define BODYELEMENT_H

#include <string>

namespace analyzer {
  namespace interpreter {
    namespace HTML {
      class BodyElement
      {
      public:
        virtual std::string ToString() = 0;
      };
    }
  }
}
#endif