/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "File.h"
#include "AnalyzerLib\interpreter\InterpreterFactory.h"

#include <regex>

namespace analyzer{
  namespace core{
    File::File()
      : data(new std::vector<unsigned char>()), fileName(), path(), interpreter(), emptyText("No data available.")
    {

    }

    File::File(const std::string & fileName, const std::vector<unsigned char> & data)
      : data(new std::vector<unsigned char>(data)), fileName(fileName), path(), interpreter(), emptyText("No data available.")
    {
      this->setDirectoryNames(fileName, "/");
      this->interpreter = analyzer::interpreter::InterpreterFactory::GetInstance()->CreateInterpreter(this->data);
    }

    File::File(const File& other)
      : data(other.data),
      fileName(other.fileName), path(other.path), interpreter(other.interpreter), emptyText(other.emptyText)
    {
    }

    File& File::operator=(const File & other)
    {
      if (this != &other){
        this->data = other.data;
        this->fileName = other.fileName;
        this->path = other.path;
        this->interpreter = other.interpreter;
        this->emptyText = other.emptyText;
      }
      return *this;
    }

    File::~File()
    {
    }

    void File::SetFileData(const std::string & fileName, const std::vector<unsigned char> & data)
    {
      this->data.reset(new std::vector<unsigned char>(data));
      this->fileName = fileName;
      this->setDirectoryNames(fileName, "/");
      this->interpreter = analyzer::interpreter::InterpreterFactory::GetInstance()->CreateInterpreter(this->data);
    }

    bool File::IsLoaded()
    {
      if (this->data.get()->size() > 0 && !this->fileName.empty()){
        return true;
      }
      else{
        return false;
      }
    }

    size_t File::GetSize()
    {
      return this->data.get()->size();
    }

    const std::string & File::GetFileName()
    {
      return this->fileName;
    }

    const std::shared_ptr<std::vector<unsigned char>> & File::GetData()
    {
      return this->data;
    }

    const std::vector<std::string> & File::GetPath()
    {
      return this->path;
    }

    bool File::UseRichText()
    {
      if (this->interpreter) {
        return this->interpreter->UseRichText();
      }
      return false;
    }

    const std::string & File::GetText()
    {
      if (this->interpreter) {
        return this->interpreter->GetText();
      }
      return this->emptyText;
    }

    void File::setDirectoryNames(const std::string& input, const std::string& regex)
    {
      std::regex re(regex);
      std::sregex_token_iterator first{ input.begin(), input.end(), re, -1 }, last;
      std::vector<std::string> parts{ first, last };
      if (parts.size() > 0){
        parts.erase(parts.begin() + parts.size() - 1);
      }
      this->path = parts;
    }
  }
}