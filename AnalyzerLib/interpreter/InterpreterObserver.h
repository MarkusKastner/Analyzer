/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef INTERPRETERBSERVER_H
#define INTERPRETERBSERVER_H

#include <memory>

namespace analyzer {
  namespace core {
    class File;
  }
  namespace interpreter {
    class InterpreterObserver
    {
    public:
      virtual void AddInternalFile(const std::shared_ptr<core::File> & internalFile) = 0;
    };
  }
}
#endif