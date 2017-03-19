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

#include "AnalyzerLib\base\BaseData.h"
#include "AnalyzerLib\interpreter\Interpreter.h"
#include "AnalyzerLib\core\FileInfo.h"
#include "AnalyzerLib\interpreter\InterpreterObserver.h"

namespace analyzer{
  namespace core{
    class FileObserver;
    class File : public interpreter::InterpreterObserver
    {
    public:
      File();
      explicit File(const std::string & fileName);
      virtual ~File();

      virtual bool IsLoaded() = 0;
      virtual size_t GetSize() = 0;

      const std::string & GetFileName();
      const std::vector<std::string> & GetPath();

      bool UseRichText();
      const std::string & GetText();
      core::FileFormat GetFileFormat();

      std::shared_ptr<interpreter::Interpreter> GetInterpreter();

      virtual void AddInternalFile(const std::shared_ptr<analyzer::core::File> & internalFile);
      bool HasInternalFiles();

      void RegisterFileObserver(FileObserver * fileObserver);
      void UnregisterFileObserver(FileObserver * fileObserver);

    protected:
      void setFileName(const std::string & fileName);
      void setDirectoryNames(const std::string& input, const std::string& regex);

      void setInterpreter(const std::shared_ptr<interpreter::Interpreter> & interpreter);
      const std::shared_ptr<interpreter::Interpreter> & getInterpreter() const;
      bool hasInterpreter();

    private:
      std::string fileName;
      std::vector<std::string> path;
      std::shared_ptr<interpreter::Interpreter> interpreter;
      std::string emptyText;
      std::vector<std::shared_ptr<analyzer::core::File>> internalFiles;
      std::vector<FileObserver*> fileObservers;

      void notifyNewInternalFile(const std::shared_ptr<analyzer::core::File> & file);
    };
  }
}

#endif