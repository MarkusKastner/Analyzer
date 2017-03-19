/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef FILEOBSERVER_H
#define FILEOBSERVER_H

#include <memory>
#include "AnalyzerLib\core\File.h"

namespace analyzer {
  namespace core {
    class FileObserver
    {
    public:
      virtual void AddInternalFile(const std::shared_ptr<File> & file) = 0;
    };
  }
}
#endif