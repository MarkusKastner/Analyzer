#include "File.h"

#include <regex>
#include "AnalyzerLib\interpreter\TextStyleInterpreter.h"
#include "AnalyzerLib\interpreter\BinaryStyleInterpreter.h"

namespace analyzer{
  namespace core{
    File::File()
      : data(new std::shared_ptr<ByteCollection>(new ByteCollection())), 
      fileName(new std::string()), path(new std::vector<std::string>()),
      textInterpreter(new std::shared_ptr<interpreter::Interpreter>(new interpreter::TextStyleInterpreter())),
      binaryInterpreter(new std::shared_ptr<interpreter::Interpreter>(new interpreter::BinaryStyleInterpreter())),
      formatFinder()
    {

    }

    File::File(const std::string & fileName, const std::vector<char> & data)
      : data(new std::shared_ptr<ByteCollection>(new ByteCollection(data))), 
      fileName(new std::string(fileName)), path(new std::vector<std::string>()),
      textInterpreter(new std::shared_ptr<interpreter::Interpreter>(new interpreter::TextStyleInterpreter())),
      binaryInterpreter(new std::shared_ptr<interpreter::Interpreter>(new interpreter::BinaryStyleInterpreter())),
      formatFinder()
    {
      this->setDirectoryNames(fileName, "/");
      this->feedInterpreter();
    }

    File::File(const File& other)
      : data(new std::shared_ptr<ByteCollection>(*other.data)), 
      fileName(new std::string(*other.fileName)), path(new std::vector<std::string>(*other.path)),
      textInterpreter(new std::shared_ptr<interpreter::Interpreter>(*other.textInterpreter)),
      binaryInterpreter(new std::shared_ptr<interpreter::Interpreter>(*other.binaryInterpreter)),
      formatFinder()
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

    const std::shared_ptr<interpreter::Interpreter> & File::GetTextInterpreter()
    {
      return *this->textInterpreter;
    }

    const std::shared_ptr<interpreter::Interpreter> & File::GetBinaryInterpreter()
    {
      return *this->binaryInterpreter;
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