/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef ANALYZERBASE_H
#define ANALYZERBASE_H

#if _USRDLL
#define IMEX __declspec(dllexport)
#else
#define IMEX __declspec(dllimport)
#endif

#include <memory>
#include <vector>
#include <thread>
#include <atomic>
#include <queue>
#include <chrono>
#include <mutex>
#include <condition_variable>

#include "AnalyzerLib\core\File.h"

namespace analyzer{
  namespace interpreter{
    class Interpreter;
  }
  namespace base{
    class AnalyzerBaseObserver;
    class IMEX AnalyzerBase
    {
    public:

      enum Task
      {
        LoadNewDataFromFile = 0
      };

      AnalyzerBase();
      virtual ~AnalyzerBase();

      bool HasActivefile();
      core::File * CurrentFile();

      size_t NumberOfObservers();
      void RegisterObserver(AnalyzerBaseObserver * observer);
      void UnregisterObserver(AnalyzerBaseObserver * observer);

      void OpenDocument(const std::string & path);
      void CloseDocument();

      bool HasData();

      void Rethrow();

      void AddAnalyzerFile(core::File & file);
      bool HasFiles();
      bool HasFile(const std::string & fileName);
      size_t FileCount();
      core::File GetAnalyzerFile(const std::string & fileName);
      core::File GetAnalyzerFile(const size_t & index);
      core::File * GetActiveAnalyzerFile();
      std::vector<std::string> GetFileNames();
      void SetActiveFile(const std::string & fileName);
      void SetNewDisplayOptions(const BaseFormat & baseFormat, const DetailFormat & detailFormat);
 
    private:
      std::thread * baseThread;
      std::atomic<bool> * runBaseWorker;
      std::condition_variable * workCondition;
      std::mutex * waitLock;
      std::exception_ptr * workerException;

      std::queue<Task> * workTasks;

      std::string * documentPath;
      std::vector<AnalyzerBaseObserver*> * baseObservers;
      
      std::recursive_mutex * workTasksLock;
      
      std::vector<core::File> * files;
      std::recursive_mutex * filesLock;

      void baseWorker();
      bool hasTask();
      Task getNextTask();
      void addTask(const Task & task);

      void loadFile();
      void loadSimpleFile();
      void loadContainer();

      void notifyInterpreterChange();
      void notifyFilesChange();

      void throwInvalidObserver(AnalyzerBaseObserver * observer);
    };
  }
}
#endif