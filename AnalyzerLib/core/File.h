#ifndef FILE_H
#define FILE_H

#include <string>
#include <vector>
#include <memory>

#include "ByteCollection.h"

#if _USRDLL
#define IMEX __declspec(dllexport)
#else
#define IMEX __declspec(dllimport)
#endif

namespace analyzer{
  namespace core{
    class IMEX File
    {
    public:
      File();
      explicit File(const std::string & fileName, const std::vector<char> & data);
      File(const File & other);
      File& operator=(const File & other);
      virtual ~File();

      void SetFileData(const std::string & fileName, const std::vector<char> & data);
      bool IsLoaded();

      const std::string & GetFileName();
      const std::shared_ptr<ByteCollection> & GetData();
      const std::vector<std::string> & GetPath();

    private:
      std::shared_ptr<ByteCollection> * data;
      std::string * fileName;
      std::vector<std::string> * path;

      void setDirectoryNames(const std::string& input, const std::string& regex);
    };
  }
}

#endif