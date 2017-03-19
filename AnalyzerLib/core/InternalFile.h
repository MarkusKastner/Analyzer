/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef INTERNALFILE_H
#define INTERNALFILE_H

#include <string>
#include <vector>
#include <memory>

#include "AnalyzerLib\core\File.h"

namespace analyzer {
  namespace core {
    class InternalFile : public File
    {
    public:
      InternalFile();
      explicit InternalFile(const std::string & fileName, const std::shared_ptr<std::vector<unsigned char>> & data, const size_t & indexBegin, const size_t & offset);
      InternalFile(const InternalFile & other);
      virtual ~InternalFile();

      void SetFileData(const std::string & fileName, const std::shared_ptr<std::vector<unsigned char>> & data, const size_t & indexBegin, const size_t & offset);

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