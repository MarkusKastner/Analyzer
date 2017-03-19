/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef PRIMARYFILE_H
#define PRIMARYFILE_H

#include <string>
#include <vector>
#include <memory>

#include "AnalyzerLib\core\File.h"

namespace analyzer {
  namespace core {
    class PrimaryFile : public File
    {
    public:
      PrimaryFile();
      explicit PrimaryFile(const std::string & fileName, const std::vector<unsigned char> & data);
      PrimaryFile(const PrimaryFile & other);
      virtual ~PrimaryFile();

      void SetFileData(const std::string & fileName, const std::vector<unsigned char> & data);
      
      virtual bool IsLoaded();
      virtual size_t GetSize();

      const std::shared_ptr<std::vector<unsigned char>> & GetData();

    private:
      std::shared_ptr<std::vector<unsigned char>> data;
      std::string emptyText;
    };
  }
}

#endif