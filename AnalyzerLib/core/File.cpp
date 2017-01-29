/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "File.h"

#include <regex>
#include "AnalyzerLib\interpreter\TextChangedObserver.h"

namespace analyzer{
  namespace core{
    File::File()
      : data(new std::vector<unsigned char>()), fileName(), path(),
      textInterpreter(), binaryInterpreter(), currentBaseFormat(base::BaseFormat::binary)
    {

    }

    File::File(const std::string & fileName, const std::vector<unsigned char> & data)
      : data(new std::vector<unsigned char>(data)), fileName(fileName), path(),
      textInterpreter(), binaryInterpreter(), currentBaseFormat(base::BaseFormat::binary)
    {
      this->setDirectoryNames(fileName, "/");
      this->feedInterpreter();
    }

    File::File(const File& other)
      : data(other.data),
      fileName(other.fileName), path(other.path),
      textInterpreter(data), binaryInterpreter(data), currentBaseFormat(other.currentBaseFormat)
    {
    }

    File& File::operator=(const File & other)
    {
      if (this != &other){
        this->data = other.data;
        this->fileName = other.fileName;
        this->path = other.path;
        this->currentBaseFormat = other.currentBaseFormat;
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
      this->feedInterpreter();
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

    std::shared_ptr<std::wstring> File::GetText()
    {
      if (this->currentBaseFormat == analyzer::base::BaseFormat::text){
        return this->textInterpreter.GetText();
      }
      else{
        return this->binaryInterpreter.GetText();
      }
    }

    std::vector<std::wstring> File::GetFunctionalHighlightExpressions()
    {
      if (this->currentBaseFormat == analyzer::base::BaseFormat::text){
        return this->textInterpreter.GetFunctionalHighlightExpressions();
      }
      else{
        return this->binaryInterpreter.GetFunctionalHighlightExpressions();
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
        this->textInterpreter.SetDetailFormat(detailFormat, forceNotify);
      }
      else if (this->currentBaseFormat == base::BaseFormat::binary){
        this->binaryInterpreter.SetDetailFormat(detailFormat, forceNotify);
      }
    }

    void File::RegisterObserver(interpreter::TextChangedObserver * observer)
    {
      this->binaryInterpreter.RegisterObserver(observer);
      this->textInterpreter.RegisterObserver(observer);
    }

    void File::UnregisterObserver(interpreter::TextChangedObserver * observer)
    {
      this->binaryInterpreter.UnregisterObserver(observer);
      this->textInterpreter.UnregisterObserver(observer);
    }

    std::vector<analyzer::base::DetailFormat> File::GetBinaryInterpreterOptions()
    {
      std::vector<analyzer::base::DetailFormat> options;
      options.push_back(base::DetailFormat::bits);
      options.push_back(base::DetailFormat::hex);
      return options;
    }

    std::vector<analyzer::base::DetailFormat> File::GetTextInterpreterOptions()
    {
      std::vector<analyzer::base::DetailFormat> options;
      options.push_back(base::DetailFormat::simpleText);

      if (this->textInterpreter.IsXML()) {
        options.push_back(base::DetailFormat::xml);
      }
      return options;
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

    void File::feedInterpreter()
    {
      this->textInterpreter.ResetData(this->data);
      this->binaryInterpreter.ResetData(this->data);
    }
  }
}