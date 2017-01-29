/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef FILE_H
#define FILE_H

#include <string>
#include <vector>
#include <memory>

#include "AnalyzerLib\interpreter\TextStyleInterpreter.h"
#include "AnalyzerLib\interpreter\BinaryStyleInterpreter.h"
#include "AnalyzerLib\base\BaseData.h"

namespace analyzer{
  namespace interpreter{
    class TextChangedObserver;
  }
  namespace core{
    class File
    {
    public:
      File();
      explicit File(const std::string & fileName, const std::vector<unsigned char> & data);
      File(const File & other);
      File& operator=(const File & other);
      virtual ~File();

      void SetFileData(const std::string & fileName, const std::vector<unsigned char> & data);
      bool IsLoaded();

      size_t GetSize();

      const std::string & GetFileName();
      const std::shared_ptr<std::vector<unsigned char>> & GetData();
      const std::vector<std::string> & GetPath();

      std::shared_ptr<std::wstring> GetText();
      std::vector<std::wstring> GetFunctionalHighlightExpressions();

      void SetDisplayOptions(const analyzer::base::BaseFormat & baseFormat, const analyzer::base::DetailFormat & detailFormat);

      void RegisterObserver(interpreter::TextChangedObserver * observer);
      void UnregisterObserver(interpreter::TextChangedObserver * observer);

      std::vector<analyzer::base::DetailFormat> GetBinaryInterpreterOptions();
      std::vector<analyzer::base::DetailFormat> GetTextInterpreterOptions();

    private:
      std::shared_ptr<std::vector<unsigned char>> data;
      std::string fileName;
      std::vector<std::string> path;
      interpreter::TextStyleInterpreter textInterpreter;
      interpreter::BinaryStyleInterpreter binaryInterpreter;
      base::BaseFormat currentBaseFormat;

      void setDirectoryNames(const std::string& input, const std::string& regex);
      void feedInterpreter();
    };
  }
}

#endif