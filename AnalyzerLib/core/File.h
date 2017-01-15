/* Copyright (C) 2016 - 2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef FILE_H
#define FILE_H

#include <string>
#include <vector>
#include <memory>

#include "ByteCollection.h"
#include "AnalyzerLib\interpreter\Interpreter.h"
#include "AnalyzerLib\core\FormatFinder.h"
#include "AnalyzerLib\base\BaseData.h"

#if _USRDLL
#define IMEX __declspec(dllexport)
#else
#define IMEX __declspec(dllimport)
#endif

namespace analyzer{
  namespace interpreter{
    class TextChangedObserver;
  }
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

      std::shared_ptr<std::wstring> GetText();
      std::vector<std::wstring> GetFunctionalHighlightExpressions();

      void SetDisplayOptions(const analyzer::base::BaseFormat & baseFormat, const analyzer::base::DetailFormat & detailFormat);

      void RegisterObserver(interpreter::TextChangedObserver * observer);
      void UnregisterObserver(interpreter::TextChangedObserver * observer);

    private:
      std::shared_ptr<ByteCollection> * data;
      std::string * fileName;
      std::vector<std::string> * path;
      std::shared_ptr<interpreter::Interpreter> * textInterpreter;
      std::shared_ptr<interpreter::Interpreter> * binaryInterpreter;
      FormatFinder formatFinder;
      base::BaseFormat currentBaseFormat;

      void setDirectoryNames(const std::string& input, const std::string& regex);
      void feedInterpreter();
    };
  }
}

#endif