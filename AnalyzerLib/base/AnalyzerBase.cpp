#include "AnalyzerBase.h"

#include <fstream>

#include "AnalyzerLib\interpreter\Interpreter.h"
#include "AnalyzerLib\interpreter\BinaryStyleInterpreter.h"
#include "AnalyzerLib\interpreter\TextStyleInterpreter.h"
#include "AnalyzerLib\base\error\AnalyzerBaseException.h"
#include "AnalyzerBaseObserver.h"

namespace analyzer{
  namespace base{
    AnalyzerBase::AnalyzerBase()
      : baseThread(nullptr), runBaseWorker(new std::atomic<bool>(true)),
      workCondition(new std::condition_variable()), waitLock(new std::mutex),// hasException(new std::atomic<bool>(true)), 
      workerException(new std::exception_ptr()),
      workTasks(new std::queue<Task>()),
      currentFilePath(new std::string()), interpreter(new std::unique_ptr<interpreter::Interpreter>()), 
      baseObservers(new std::vector<AnalyzerBaseObserver*>())
    {
      this->interpreter->reset(new interpreter::BinaryStyleInterpreter());
      this->baseThread = new std::thread(&AnalyzerBase::baseWorker, this);
    }

    AnalyzerBase::~AnalyzerBase()
    {
      *this->runBaseWorker = false;

      if (this->baseThread != nullptr){
        //*this->baseWorkerNotified = true;
        this->workCondition->notify_one();
        this->baseThread->join();
        delete this->baseThread;
      }

      delete this->workCondition;
      delete this->waitLock;
      //delete this->hasException;
      //delete this->workerException;
      delete this->workTasks;
      delete this->runBaseWorker;
      delete this->currentFilePath;
      delete this->interpreter;
      delete this->baseObservers;
    }

    bool AnalyzerBase::HasInterpreter()
    {
      return !(!interpreter);
    }

    interpreter::Interpreter * AnalyzerBase::Interpreter()
    {
      return this->interpreter->get();
    }

    void AnalyzerBase::SetBinaryMode()
    {
      if (!dynamic_cast<interpreter::BinaryStyleInterpreter*>(this->interpreter->get())){
        this->interpreter->reset(new interpreter::BinaryStyleInterpreter());
        this->notifyInterpreterChange();
      }
    }

    void AnalyzerBase::SetTextMode()
    {
      if (!dynamic_cast<interpreter::TextStyleInterpreter*>(this->interpreter->get())){
        this->interpreter->reset(new interpreter::TextStyleInterpreter());
        this->notifyInterpreterChange();
      }
    }

    size_t AnalyzerBase::NumberOfObservers()
    {
      return this->baseObservers->size();
    }

    void AnalyzerBase::RegisterObserver(AnalyzerBaseObserver * observer)
    {
      this->throwInvalidObserver(observer);
      for (auto it = this->baseObservers->begin(); it != this->baseObservers->end(); ++it){
        if ((*it) == observer){
          return;
        }
      }
      this->baseObservers->push_back(observer);
    }

    void AnalyzerBase::UnregisterObserver(AnalyzerBaseObserver * observer)
    {
      this->throwInvalidObserver(observer);
      for (auto it = this->baseObservers->begin(); it != this->baseObservers->end(); ++it){
        if ((*it) == observer){
          this->baseObservers->erase(it);
          return;
        }
      }
    }

    void AnalyzerBase::LoadFile(const std::string & path)
    {
      *this->currentFilePath = path;
      this->workTasks->push(Task::LoadNewDataFromFile);
      this->workCondition->notify_one();
    }

    bool AnalyzerBase::HasData()
    {
      return this->interpreter->get()->HasData();
    }

    void AnalyzerBase::Rethrow()
    {
      if (*this->workerException){
        std::rethrow_exception(*this->workerException);
      }
    }

    void AnalyzerBase::baseWorker()
    {
      std::unique_lock<std::mutex> lock(*this->waitLock);
      while (this->runBaseWorker->load()){
        try{
          this->workCondition->wait(lock);
          while (!this->workTasks->empty()){
            
            switch (this->workTasks->front()){
            case Task::LoadNewDataFromFile:
              this->loadFile();
              this->workTasks->pop();
              break;
            }
          }
        }
        catch (...){
          *this->workerException = std::current_exception();
          //*this->hasException = true;
          break;
        }
      }
    }

    void AnalyzerBase::loadFile()
    {
      std::ifstream file(this->currentFilePath->c_str(), std::ios::binary);
      if (file.bad() || !file.is_open()){
        throw AnalyzerBaseException("Cannot open " + *this->currentFilePath);
      }

      std::vector<char> data;

      long fileSize = 0;
      file.seekg(0, std::ios::end);
      fileSize = file.tellg();
      file.seekg(0, std::ios::beg);

      data.reserve(fileSize);
      data.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
      this->interpreter->get()->ResetData(data);
    }

    void AnalyzerBase::notifyInterpreterChange()
    {
      for (auto observer : *this->baseObservers){
        observer->NotifyInterprterChange();
      }
    }

    void AnalyzerBase::throwInvalidObserver(AnalyzerBaseObserver * observer)
    {
      if (nullptr == observer){
        throw AnalyzerBaseException("Invalid base observer");
      }
    }
  }
}