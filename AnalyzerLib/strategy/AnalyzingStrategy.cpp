/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "AnalyzingStrategy.h"

namespace analyzer{
  namespace strategy{
    AnalyzingStrategy::AnalyzingStrategy()
      : defSource(new std::shared_ptr<definition::DefinitionSource>()),
      data(new std::shared_ptr<analyzer::core::ByteCollection>()),
      results(new std::vector<std::shared_ptr<Result>>()),
      analyzingThread(nullptr), isAnalyzing(new std::atomic<bool>(false)),
      sourceLock(new std::recursive_mutex()), 
      dataLock(new std::recursive_mutex()),
      resultLock(new std::recursive_mutex())
    {

    }

    AnalyzingStrategy::~AnalyzingStrategy()
    {
      delete this->defSource;
      delete this->data;
      delete this->results;

      if (this->analyzingThread != nullptr){
        if (this->analyzingThread->joinable()){
          this->analyzingThread->join();
        }
        delete this->analyzingThread;
      }

      delete this->sourceLock;
      delete this->dataLock;
      delete this->isAnalyzing;
      delete this->resultLock;
    }

    void AnalyzingStrategy::SetDefinitions(const std::shared_ptr<definition::DefinitionSource> & definitionSource)
    {
      std::lock_guard<std::recursive_mutex> lockDef(*this->sourceLock);
      *this->defSource = definitionSource;
    }

    bool AnalyzingStrategy::HasDefinitionSource()
    {
      std::lock_guard<std::recursive_mutex> lockDef(*this->sourceLock);
      if (*this->defSource){
        return true;
      }
      return false;
    }

    void AnalyzingStrategy::SetData(const std::shared_ptr<analyzer::core::ByteCollection> & data)
    {
      std::lock_guard<std::recursive_mutex> lockData(*this->dataLock);
      *this->data = data;
    }
    
    bool AnalyzingStrategy::HasData()
    {
      std::lock_guard<std::recursive_mutex> lockData(*this->dataLock);
      if (*this->data){
        return true;
      }
      return false;
    }

    void AnalyzingStrategy::StartAnalyzing()
    {
      *this->isAnalyzing = true;
      this->analyzingThread = new std::thread(&AnalyzingStrategy::analyzingRoutine, this);
    }

    bool AnalyzingStrategy::IsAnalyzing()
    {
      return *this->isAnalyzing;
    }

    const std::vector<std::shared_ptr<Result>> & AnalyzingStrategy::GetResults()
    {
      std::lock_guard<std::recursive_mutex> lockRes(*this->resultLock);
      return *this->results;
    }

    void AnalyzingStrategy::addResult(const std::shared_ptr<Result> & result)
    {
      if (this->hasResult(result)){
        return;
      }
      std::lock_guard<std::recursive_mutex> lockRes(*this->resultLock);
      this->results->push_back(result);
    }

    void AnalyzingStrategy::analyzingRoutine()
    {
      std::lock_guard<std::recursive_mutex> lockDef(*this->sourceLock);
      std::lock_guard<std::recursive_mutex> lockData(*this->dataLock);
      this->analyze(*this->defSource, *this->data);

      *this->isAnalyzing = false;
    }

    bool AnalyzingStrategy::hasResult(const std::shared_ptr<Result> & result)
    {
      std::lock_guard<std::recursive_mutex> lockRes(*this->resultLock);
      for (auto& res : (*this->results)){
        if (this->compareResult(res, result)){
          return true;
        }
      }
      return false;
    }
  }
}