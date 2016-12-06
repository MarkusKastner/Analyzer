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

      bool HasInterpreter();
      interpreter::Interpreter * Interpreter();

      void SetBinaryMode();
      void SetTextMode();

      size_t NumberOfObservers();
      void RegisterObserver(AnalyzerBaseObserver * observer);
      void UnregisterObserver(AnalyzerBaseObserver * observer);

      void LoadFile(const std::string & path);
      bool HasData();

      void Rethrow();

    private:
      std::thread * baseThread;
      std::atomic<bool> * runBaseWorker;
      std::condition_variable * workCondition;
      std::mutex * waitLock;
      std::exception_ptr * workerException;

      std::queue<Task> * workTasks;

      std::string * currentFilePath;
      std::unique_ptr<interpreter::Interpreter> * interpreter;
      std::vector<AnalyzerBaseObserver*> * baseObservers;

      std::recursive_mutex * workTasksLock;

      void baseWorker();
      bool hasTask();
      Task getNextTask();
      void addTask(const Task & task);

      void loadFile();

      void notifyInterpreterChange();

      void throwInvalidObserver(AnalyzerBaseObserver * observer);
    };
  }
}
#endif