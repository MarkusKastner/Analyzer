#include "File.h"

#include <regex>

namespace analyzer{
  namespace core{
    File::File()
      : data(new std::shared_ptr<ByteCollection>(new ByteCollection())), fileName(new std::string()), path(new std::vector<std::string>())
    {

    }

    File::File(const std::string & fileName, const std::vector<char> & data)
      : data(new std::shared_ptr<ByteCollection>(new ByteCollection(data))), fileName(new std::string(fileName)), path(new std::vector<std::string>())
    {
      this->setDirectoryNames(fileName, "/");
    }

    File::~File()
    {
      delete this->data;
      delete this->fileName;
      delete this->path;
    }

    void File::SetFileData(const std::string & fileName, const std::vector<char> & data)
    {
      this->data->reset(new ByteCollection(data));
      *this->fileName = fileName;
      this->setDirectoryNames(fileName, "/");
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

  }
}