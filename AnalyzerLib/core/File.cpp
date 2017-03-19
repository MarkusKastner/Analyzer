/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "File.h"
#include "AnalyzerLib\interpreter\InterpreterFactory.h"
#include "AnalyzerLib\core\FileObserver.h"

#include <regex>

namespace analyzer{
  namespace core{
    File::File()
      : fileName(), path(), interpreter(), emptyText("No data available."), internalFiles(), fileObservers()
    {
    }

    File::File(const std::string & fileName)
      : fileName(fileName), path(), interpreter(), emptyText("No data available."), internalFiles(), fileObservers()
    {
    }

    File::~File()
    {
    }

    const std::string & File::GetFileName()
    {
      return this->fileName;
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

    core::FileFormat File::GetFileFormat()
    {
      if (this->interpreter) {
        return this->interpreter->GetFileFormat();
      }
      return core::FileFormat::empty;
    }

    std::shared_ptr<interpreter::Interpreter> File::GetInterpreter()
    {
      return this->interpreter;
    }

    void File::AddInternalFile(const std::shared_ptr<analyzer::core::File> & internalFile)
    {
      std::string newSubFileName(this->fileName + "/" + internalFile->GetFileName());
      internalFile->setFileName(newSubFileName);
      this->internalFiles.push_back(internalFile);
      this->notifyNewInternalFile(internalFile);
    }

    bool File::HasInternalFiles()
    {
      return !this->internalFiles.empty();
    }

    void File::RegisterFileObserver(FileObserver * fileObserver)
    {
      for (auto it = this->fileObservers.begin(); it != this->fileObservers.end(); ++it) {
        if ((*it) == fileObserver) {
          return;
        }
      }
      this->fileObservers.push_back(fileObserver);
    }

    void File::UnregisterFileObserver(FileObserver * fileObserver)
    {
      for (auto it = this->fileObservers.begin(); it != this->fileObservers.end(); ++it) {
        if ((*it) == fileObserver) {
          this->fileObservers.erase(it);
          return;
        }
      }
    }

    void File::setFileName(const std::string & fileName)
    {
      this->fileName = fileName;
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

    void File::setInterpreter(const std::shared_ptr<interpreter::Interpreter> & interpreter)
    {
      this->interpreter = interpreter;
      if (this->interpreter) {
        this->interpreter->SetObserver(this);
      }
    }

    const std::shared_ptr<interpreter::Interpreter> & File::getInterpreter() const
    {
      return this->interpreter;
    }

    bool File::hasInterpreter()
    {
      return !(!this->interpreter);
    }

    void File::notifyNewInternalFile(const std::shared_ptr<analyzer::core::File>& file)
    {
      for (auto& fileObserver : this->fileObservers) {
        fileObserver->AddInternalFile(file);
      }
    }
  }
}