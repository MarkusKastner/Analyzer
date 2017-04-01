/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "InternalFile.h"
#include "AnalyzerLib\interpreter\InterpreterFactory.h"

#include <regex>

namespace analyzer {
  namespace core {
    InternalFile::InternalFile()
      : File(), data(new std::vector<unsigned char>()), emptyText("No data available."), indexBegin(0), offset(0)
    {

    }

    InternalFile::InternalFile(const std::string & fileName, const std::shared_ptr<std::vector<unsigned char>> & data, const size_t & indexBegin, const size_t & offset)
      : File(fileName), emptyText("No data available."), indexBegin(indexBegin), offset(offset)
    {
      this->setDirectoryNames(fileName, "/");
      this->data = data;
      this->setInterpreter(analyzer::interpreter::InterpreterFactory::GetInstance()->CreateInterpreter(this->data, indexBegin, offset));
    }

    InternalFile::InternalFile(const InternalFile& other)
      : File(other), data(other.data), emptyText(other.emptyText)
    {
    }

    InternalFile::~InternalFile()
    {
    }

    void InternalFile::SetFileData(const std::string & fileName, const std::shared_ptr<std::vector<unsigned char>> & data, const size_t & indexBegin, const size_t & offset)
    {
      this->indexBegin = indexBegin;
      this->offset = offset;
      this->setFileName(fileName);
      this->data = data;
      this->setDirectoryNames(fileName, "/");
      this->setInterpreter(analyzer::interpreter::InterpreterFactory::GetInstance()->CreateInterpreter(this->data, indexBegin, offset));
    }

    bool InternalFile::IsLoaded()
    {
      if (this->data.get()->size() > 0 && !this->GetFileName().empty()) {
        return true;
      }
      else {
        return false;
      }
    }

    size_t InternalFile::GetSize()
    {
      return this->offset;
    }

    const std::shared_ptr<std::vector<unsigned char>> & InternalFile::GetData()
    {
      return this->data;
    }

    std::shared_ptr<std::vector<unsigned char>> InternalFile::cloneData()
    {
      std::vector<unsigned char>::const_iterator first = this->data->begin() + this->indexBegin;
      std::vector<unsigned char>::const_iterator last = this->data->begin() + (this->indexBegin + this->offset);
      return std::shared_ptr<std::vector<unsigned char>>(new std::vector<unsigned char>(first, last));
    }
  }
}