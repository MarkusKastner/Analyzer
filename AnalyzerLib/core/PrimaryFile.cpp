/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "PrimaryFile.h"
#include "AnalyzerLib\interpreter\InterpreterFactory.h"

#include <regex>

namespace analyzer {
  namespace core {
    PrimaryFile::PrimaryFile()
      : File(), data(new std::vector<unsigned char>()), emptyText("No data available.")
    {

    }

    PrimaryFile::PrimaryFile(const std::string & fileName, const std::vector<unsigned char> & data)
      : File(fileName), data(new std::vector<unsigned char>(data)), emptyText("No data available.")
    {
      this->setDirectoryNames(fileName, "/");
      this->setInterpreter(analyzer::interpreter::InterpreterFactory::GetInstance()->CreateInterpreter(this->data));
    }

    PrimaryFile::PrimaryFile(const PrimaryFile& other)
      : File(other), data(other.data), emptyText(other.emptyText)
    {
    }

    PrimaryFile::~PrimaryFile()
    {
    }

    void PrimaryFile::SetFileData(const std::string & fileName, const std::vector<unsigned char> & data)
    {
      this->setFileName(fileName);
      this->data.reset(new std::vector<unsigned char>(data));
      this->setDirectoryNames(fileName, "/");
      this->setInterpreter(analyzer::interpreter::InterpreterFactory::GetInstance()->CreateInterpreter(this->data));
    }

    bool PrimaryFile::IsLoaded()
    {
      if (this->data.get()->size() > 0 && !this->GetFileName().empty()) {
        return true;
      }
      else {
        return false;
      }
    }

    size_t PrimaryFile::GetSize()
    {
      return this->data.get()->size();
    }

    const std::shared_ptr<std::vector<unsigned char>> & PrimaryFile::GetData()
    {
      return this->data;
    }
  }
}