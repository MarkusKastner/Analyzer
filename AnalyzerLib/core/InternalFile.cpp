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
      : File(), data(new std::vector<unsigned char>()), emptyText("No data available.")
    {

    }

    InternalFile::InternalFile(const std::string & fileName, const std::shared_ptr<std::vector<unsigned char>> & data, const size_t & indexBegin, const size_t & offset)
      : File(fileName), emptyText("No data available.")
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
      return this->data.get()->size();
    }

    const std::shared_ptr<std::vector<unsigned char>> & InternalFile::GetData()
    {
      return this->data;
    }
  }
}