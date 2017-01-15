/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "File.h"

#include <regex>
#include "AnalyzerLib\interpreter\TextStyleInterpreter.h"
#include "AnalyzerLib\interpreter\BinaryStyleInterpreter.h"
#include "AnalyzerLib\interpreter\TextChangedObserver.h"

namespace analyzer{
  namespace core{
    File::File()
      : data(new std::shared_ptr<ByteCollection>(new ByteCollection())), 
      fileName(new std::string()), path(new std::vector<std::string>()),
      textInterpreter(new std::shared_ptr<interpreter::Interpreter>(new interpreter::TextStyleInterpreter())),
      binaryInterpreter(new std::shared_ptr<interpreter::Interpreter>(new interpreter::BinaryStyleInterpreter())),
      formatFinder(), currentBaseFormat(base::BaseFormat::binary)
    {

    }

    File::File(const std::string & fileName, const std::vector<char> & data)
      : data(new std::shared_ptr<ByteCollection>(new ByteCollection(data))), 
      fileName(new std::string(fileName)), path(new std::vector<std::string>()),
      textInterpreter(new std::shared_ptr<interpreter::Interpreter>(new interpreter::TextStyleInterpreter())),
      binaryInterpreter(new std::shared_ptr<interpreter::Interpreter>(new interpreter::BinaryStyleInterpreter())),
      formatFinder(), currentBaseFormat(base::BaseFormat::binary)
    {
      this->setDirectoryNames(fileName, "/");
      this->feedInterpreter();
    }

    File::File(const File& other)
      : data(new std::shared_ptr<ByteCollection>(*other.data)), 
      fileName(new std::string(*other.fileName)), path(new std::vector<std::string>(*other.path)),
      textInterpreter(new std::shared_ptr<interpreter::Interpreter>(*other.textInterpreter)),
      binaryInterpreter(new std::shared_ptr<interpreter::Interpreter>(*other.binaryInterpreter)),
      formatFinder(), currentBaseFormat(other.currentBaseFormat)
    {
    }

    File& File::operator=(const File & other)
    {
      if (this != &other){
        *this->data = *other.data;
        *this->fileName = *other.fileName;
        *this->path = *other.path;
        *this->textInterpreter = *other.textInterpreter;
        *this->binaryInterpreter = *other.binaryInterpreter;
        this->currentBaseFormat = other.currentBaseFormat;
      }
      return *this;
    }

    File::~File()
    {
      delete this->data;
      delete this->fileName;
      delete this->path;
      delete this->textInterpreter;
      delete this->binaryInterpreter;
    }

    void File::SetFileData(const std::string & fileName, const std::vector<char> & data)
    {
      this->data->reset(new ByteCollection(data));
      *this->fileName = fileName;
      this->setDirectoryNames(fileName, "/");
      this->feedInterpreter();
    }

    bool File::IsLoaded()
    {
      if (this->data->get()->GetSize() > 0 && !this->fileName->empty()){
        return true;
      }
      else{
        return false;
      }
    }

    const std::string & File::GetFileName()
    {
      return *this->fileName;
    }

    const std::shared_ptr<ByteCollection> & File::GetData()
    {
      return *this->data;
    }

    const std::vector<std::string> & File::GetPath()
    {
      return *this->path;
    }

    std::shared_ptr<std::wstring> File::GetText()
    {
      if (this->currentBaseFormat == analyzer::base::BaseFormat::text){
        return this->textInterpreter->get()->GetText();
      }
      else{
        return this->binaryInterpreter->get()->GetText();
      }
    }

    std::vector<std::wstring> File::GetFunctionalHighlightExpressions()
    {
      if (this->currentBaseFormat == analyzer::base::BaseFormat::text){
        return this->textInterpreter->get()->GetFunctionalHighlightExpressions();
      }
      else{
        return this->binaryInterpreter->get()->GetFunctionalHighlightExpressions();
      }
    }

    void File::SetDisplayOptions(const analyzer::base::BaseFormat & baseFormat, const analyzer::base::DetailFormat & detailFormat)
    {
      bool forceNotify = false;
      if (this->currentBaseFormat != baseFormat){
        this->currentBaseFormat = baseFormat;
        forceNotify = true;
      }
      if (this->currentBaseFormat == base::BaseFormat::text){
        this->textInterpreter->get()->SetDetailFormat(detailFormat, forceNotify);
      }
      else if (this->currentBaseFormat == base::BaseFormat::binary){
        this->binaryInterpreter->get()->SetDetailFormat(detailFormat, forceNotify);
      }
    }

    void File::RegisterObserver(interpreter::TextChangedObserver * observer)
    {
      this->binaryInterpreter->get()->RegisterObserver(observer);
      this->textInterpreter->get()->RegisterObserver(observer);
    }

    void File::UnregisterObserver(interpreter::TextChangedObserver * observer)
    {
      this->binaryInterpreter->get()->UnregisterObserver(observer);
      this->textInterpreter->get()->UnregisterObserver(observer);
    }

    void File::setDirectoryNames(const std::string& input, const std::string& regex)
    {
      std::regex re(regex);
      std::sregex_token_iterator first{ input.begin(), input.end(), re, -1 }, last;
      std::vector<std::string> parts{ first, last };
      if (parts.size() > 0){
        parts.erase(parts.begin() + parts.size() - 1);
      }
      *this->path = parts;
    }

    void File::feedInterpreter()
    {
      this->textInterpreter->get()->ResetData(*this->data);
      this->binaryInterpreter->get()->ResetData(*this->data);
    }
  }
}